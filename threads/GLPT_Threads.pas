{ GLPT :: OpenGL Pascal Toolkit

  Copyright (c) 2020 Ryan Joseph

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
}
unit GLPT_Threads;

{$mode objfpc}

{$INCLUDE ../include/settings.inc}

interface

uses
  Classes, CTypes, GLPT,
{$IFDEF MSWINDOWS}
  Windows;
{$ENDIF}
{$IFDEF LINUX}
  Linux;
{$ENDIF}
{$IFDEF COCOA}
  SysUtils, BaseUnix, Unix;
{$ENDIF}
{$IFDEF IPHONE}
  SysUtils, BaseUnix, Unix;
{$ENDIF}

{$IFDEF DARWIN}
{$INCLUDE include/darwin/ptypes.inc}
{$INCLUDE include/darwin/pthread.inc}
{$INCLUDE include/darwin/errno.inc}
{$ENDIF}

// https://wiki.freepascal.org/Threads
// https://wiki.lazarus.freepascal.org/Multithreaded_Application_Tutorial

{ Threads }
const
  GLPT_THREAD_DEFAULT_STACK_SIZE = 4096;

type
  pGLPT_Thread = ^GLPT_Thread;
  GLPT_ThreadFunction = function (userData: pointer): integer;
  GLPT_Thread_ID = ptrint;
  GLPT_Thread = record
    start: GLPT_ThreadFunction;
    id: GLPT_Thread_ID;
    handle: pointer;
    name: string;
    userData: pointer;
    status: integer;
    stacksize: longword;
  end;

function GLPT_CreateThread(start: GLPT_ThreadFunction; 
                           name: string = ''; 
                           userData: pointer = nil; 
                           stacksize: integer = GLPT_THREAD_DEFAULT_STACK_SIZE): pGLPT_Thread;
procedure GLPT_DetachThread(thread: pGLPT_Thread);
procedure GLPT_WaitThread(var thread: pGLPT_Thread; var status: integer);
function GLPT_ThreadID: GLPT_Thread_ID;
function GLPT_RunThread(thread: pGLPT_Thread): pointer; cdecl;

{ Mutex }

type
  pGLPT_Mutex = ^GLPT_Mutex;
  GLPT_Mutex = record
    {$IFDEF DARWIN}
    handle: pthread_mutex_t; { from ptypes.inc }
    {$ENDIF}
  end;

function GLPT_CreateMutex: pGLPT_Mutex;
procedure GLPT_DestroyMutex(var mutex: pGLPT_Mutex);
function GLPT_LockMutex(mutex: pGLPT_Mutex): integer;
function GLPT_UnlockMutex(mutex: pGLPT_Mutex): integer;
function GLPT_TryLockMutex(mutex: pGLPT_Mutex): integer;

{ Condition Variable }

type
  pGLPT_Condition = ^GLPT_Condition;
  GLPT_Condition = record
    {$IFDEF DARWIN}
    handle: pthread_cond_t; { from ptypes.inc }
    {$ENDIF}
  end;

function GLPT_CreateCondition: pGLPT_Condition;
procedure GLPT_DestroyCondition(var condition: pGLPT_Condition);
function GLPT_ConditionSignal(condition: pGLPT_Condition): integer;
function GLPT_ConditionBroadcast(condition: pGLPT_Condition): integer;
function GLPT_ConditionWaitTimeout(condition: pGLPT_Condition; mutex: pGLPT_Mutex; ms: longint): integer;
function GLPT_ConditionWait(condition: pGLPT_Condition; mutex: pGLPT_Mutex): integer;

{ Semaphore }

type
  pGLPT_Semaphore = ^GLPT_Semaphore;
  GLPT_Semaphore = record
    {$IFDEF DARWIN}
    public type 
      psem_t = SizeInt; { from ptypes.inc }
    public
      handle: psem_t;
      name: string;
    {$ENDIF}
  end;

function GLPT_CreateSemaphore(initial_value: integer = 0): pGLPT_Semaphore;
procedure GLPT_DestroySemaphore(var sem: pGLPT_Semaphore);
function GLPT_SemaphoreTryWait(sem: pGLPT_Semaphore): integer;
function GLPT_SemaphoreWait(sem: pGLPT_Semaphore): integer;
function GLPT_SemaphoreWaitTimeout(sem: pGLPT_Semaphore; timeout: longint): integer;
function GLPT_SemaphoreValue(sem: pGLPT_Semaphore): integer;
function GLPT_SemaphorePost(sem: pGLPT_Semaphore): integer;

implementation

{$IFDEF MSWINDOWS}
  {$INCLUDE GLPT_gdi.inc}
{$ENDIF}
{$IFDEF LINUX}
  {$INCLUDE include/GLPT_X11.inc}
{$ENDIF}
{$IFDEF COCOA}
  {$INCLUDE include/GLPT_Darwin.inc}
{$ENDIF}
{$IFDEF IPHONE}
  {$INCLUDE include/GLPT_Darwin.inc}
{$ENDIF}

function calloc(size: ptruint): pointer;
var
  itm: pointer;
begin
  GetMem(itm, size);
  FillByte(itm^, size, 0);
  exit(itm);
end;

function GLPT_CreateSemaphore(initial_value: integer = 0): pGLPT_Semaphore;
var
  sem: pGLPT_Semaphore;
  success: boolean;
begin
  sem := pGLPT_Semaphore(calloc(sizeof(GLPT_Semaphore)));
  {$IFDEF MSWINDOWS}
    success := gdi_CreateSemaphore(sem, initial_value);
  {$ENDIF}
  {$IFDEF LINUX}
    success := X11_CreateSemaphore(sem, initial_value);
  {$ENDIF}
  {$IFDEF DARWIN}
    success := Cocoa_CreateSemaphore(sem, initial_value);
  {$ENDIF}
  if success then
    result := sem
  else
    begin
      FreeMem(sem);
      result := nil;
    end;
end;

procedure GLPT_DestroySemaphore(var sem: pGLPT_Semaphore);
begin
  if assigned(sem) then
    begin
      {$IFDEF MSWINDOWS}
        gdi_DestroySemaphore(sem);
      {$ENDIF}
      {$IFDEF LINUX}
        X11_DestroySemaphore(sem);
      {$ENDIF}
      {$IFDEF DARWIN}
        Cocoa_DestroySemaphore(sem);
      {$ENDIF}
      FreeMem(sem);
      sem := nil;
    end;
end;

function GLPT_SemaphoreTryWait(sem: pGLPT_Semaphore): integer;
begin
  if sem = nil then
    begin
      result := GLPTError(GLPT_ERROR_THREADS, 'Passed a nil semaphore"');
      exit;
    end;
  {$IFDEF MSWINDOWS}
    result := gdi_SemaphoreTryWait(sem);
  {$ENDIF}
  {$IFDEF LINUX}
    result := X11_SemaphoreTryWaitsem);
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_SemaphoreTryWait(sem);
  {$ENDIF}
end;

function GLPT_SemaphoreWait(sem: pGLPT_Semaphore): integer;
begin
    if sem = nil then
    begin
      result := GLPTError(GLPT_ERROR_THREADS, 'Passed a nil semaphore"');
      exit;
    end;
  {$IFDEF MSWINDOWS}
    result := gdi_SemaphoreWait(sem);
  {$ENDIF}
  {$IFDEF LINUX}
    result := X11_SemaphoreWait(sem);
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_SemaphoreWait(sem);
  {$ENDIF}
end;

function GLPT_SemaphoreWaitTimeout(sem: pGLPT_Semaphore; timeout: longint): integer;
begin
  if sem = nil then
    begin
      result := GLPTError(GLPT_ERROR_THREADS, 'Passed a nil semaphore"');
      exit;
    end;

  if timeout = 0 then
    begin
      result := GLPT_SemaphoreTryWait(sem);
      exit;
    end
  else if timeout = -1 then
    begin
      result := GLPT_SemaphoreWait(sem);
      exit;
    end;

  {$IFDEF MSWINDOWS}
    result := gdi_SemaphoreWaitTimeout(sem, timeout);
  {$ENDIF}
  {$IFDEF LINUX}
    result := X11_SemaphoreWaitTimeout(sem, timeout);
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_SemaphoreWaitTimeout(sem, timeout);
  {$ENDIF}
end;

function GLPT_SemaphoreValue(sem: pGLPT_Semaphore): integer;
begin
  {$IFDEF MSWINDOWS}
    result := gdi_SemValue(sem);
  {$ENDIF}
  {$IFDEF LINUX}
    result := X11_SemValue(sem);
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_SemaphoreValue(sem);
  {$ENDIF}
end;

function GLPT_SemaphorePost(sem: pGLPT_Semaphore): integer;
begin
  if sem = nil then
    begin
      result := GLPTError(GLPT_ERROR_THREADS, 'Passed a nil semaphore"');
      exit;
    end;
  {$IFDEF MSWINDOWS}
    result := gdi_SemaphorePost(sem);
  {$ENDIF}
  {$IFDEF LINUX}
    result := X11_SemaphorePost(sem);
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_SemaphorePost(sem);
  {$ENDIF}
end;

function GLPT_CreateCondition: pGLPT_Condition;
var
  condition: pGLPT_Condition;
  success: boolean;
begin
  condition := pGLPT_Condition(calloc(sizeof(GLPT_Condition)));
  {$IFDEF MSWINDOWS}
    success := gdi_CreateCondition(condition);
  {$ENDIF}
  {$IFDEF LINUX}
    success := X11_CreateCondition(condition);
  {$ENDIF}
  {$IFDEF DARWIN}
    success := Cocoa_CreateCondition(condition);
  {$ENDIF}
  if success then
    result := condition
  else
    begin
      FreeMem(condition);
      result := nil;
    end;
end;

procedure GLPT_DestroyCondition(var condition: pGLPT_Condition);
begin
  if assigned(condition) then
    begin
      {$IFDEF MSWINDOWS}
        gdi_DestroyCondition(condition);
      {$ENDIF}
      {$IFDEF LINUX}
        X11_DestroyCondition(condition);
      {$ENDIF}
      {$IFDEF DARWIN}
        Cocoa_DestroyCondition(condition);
      {$ENDIF}
      FreeMem(condition);
      condition := nil;
    end;
end;

function GLPT_ConditionSignal(condition: pGLPT_Condition): integer;
begin
  if condition = nil then
    begin
      result := GLPTError(GLPT_ERROR_THREADS, 'Passed a nil condition"');
      exit;
    end;
  {$IFDEF MSWINDOWS}
    result := gdi_ConditionSignal(condition);
  {$ENDIF}
  {$IFDEF LINUX}
    result := X11_ConditionSignal(condition);
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_ConditionSignal(condition);
  {$ENDIF}
end;

function GLPT_ConditionBroadcast(condition: pGLPT_Condition): integer;
begin
  if condition = nil then
    begin
      result := GLPTError(GLPT_ERROR_THREADS, 'Passed a nil condition"');
      exit;
    end;
  {$IFDEF MSWINDOWS}
    result := gdi_ConditionBroadcast(condition);
  {$ENDIF}
  {$IFDEF LINUX}
    result := X11_ConditionBroadcast(condition);
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_ConditionBroadcast(condition);
  {$ENDIF}
end;

function GLPT_ConditionWaitTimeout(condition: pGLPT_Condition; mutex: pGLPT_Mutex; ms: longint): integer;
begin
  if condition = nil then
    begin
      result := GLPTError(GLPT_ERROR_THREADS, 'Passed a nil condition"');
      exit;
    end;
  {$IFDEF MSWINDOWS}
    result := Cocoa_ConditionWaitTimeout(condition, mutex, ms);
  {$ENDIF}
  {$IFDEF LINUX}
    result := Cocoa_ConditionWaitTimeout(condition, mutex, ms);
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_ConditionWaitTimeout(condition, mutex, ms);
  {$ENDIF}
end;

function GLPT_ConditionWait(condition: pGLPT_Condition; mutex: pGLPT_Mutex): integer;
begin
  if condition = nil then
    begin
      result := GLPTError(GLPT_ERROR_THREADS, 'Passed a nil condition"');
      exit;
    end;
  {$IFDEF MSWINDOWS}
    result := gdi_ConditionWait(condition, mutex);
  {$ENDIF}
  {$IFDEF LINUX}
    result := X11_ConditionWait(condition, mutex);
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_ConditionWait(condition, mutex);
  {$ENDIF}
end;


function GLPT_CreateMutex: pGLPT_Mutex;
var
  mutex: pGLPT_Mutex;
  success: boolean;
begin
  mutex := pGLPT_Mutex(calloc(sizeof(GLPT_Mutex)));
  {$IFDEF MSWINDOWS}
    success := gdi_CreateMutex(mutex);
  {$ENDIF}
  {$IFDEF LINUX}
    success := X11_CreateMutex(mutex);
  {$ENDIF}
  {$IFDEF DARWIN}
    success := Cocoa_CreateMutex(mutex);
  {$ENDIF}
  if success then
    result := mutex
  else
    begin
      FreeMem(mutex);
      result := nil;
    end;
end;

procedure GLPT_DestroyMutex(var mutex: pGLPT_Mutex);
begin
  if assigned(mutex) then
    begin
      {$IFDEF MSWINDOWS}
        gdi_DestroyMutex(mutex);
      {$ENDIF}
      {$IFDEF LINUX}
        X11_DestroyMutex(mutex);
      {$ENDIF}
      {$IFDEF DARWIN}
        Cocoa_DestroyMutex(mutex);
      {$ENDIF}
      FreeMem(mutex);
      mutex := nil;
    end;
end;

function GLPT_LockMutex(mutex: pGLPT_Mutex): integer;
begin
  if mutex = nil then
    begin
      result := GLPTError(GLPT_ERROR_THREADS, 'Passed a nil mutex"');
      exit;
    end;
  {$IFDEF MSWINDOWS}
    result := gdi_LockMutex(mutex);
  {$ENDIF}
  {$IFDEF LINUX}
    result := X11_LockMutex(mutex);
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_LockMutex(mutex);
  {$ENDIF}
end;

function GLPT_UnlockMutex(mutex: pGLPT_Mutex): integer;
begin
  if mutex = nil then
    begin
      result := GLPTError(GLPT_ERROR_THREADS, 'Passed a nil mutex"');
      exit;
    end;
  {$IFDEF MSWINDOWS}
    result := gdi_UnlockMutex(mutex);
  {$ENDIF}
  {$IFDEF LINUX}
    result := X11_UnlockMutex(mutex);
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_UnlockMutex(mutex);
  {$ENDIF}
end;

function GLPT_TryLockMutex(mutex: pGLPT_Mutex): integer;
begin
  if mutex = nil then
    begin
      result := GLPTError(GLPT_ERROR_THREADS, 'Passed a nil mutex"');
      exit;
    end;
  {$IFDEF MSWINDOWS}
    result := gdi_TryLockMutex(mutex);
  {$ENDIF}
  {$IFDEF LINUX}
    result := X11_TryLockMutex(mutex);
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_TryLockMutex(mutex);
  {$ENDIF}
end;

function GLPT_ThreadID: GLPT_Thread_ID;
begin
  {$IFDEF MSWINDOWS}
    result := gdi_ThreadID;
  {$ENDIF}
  {$IFDEF LINUX}
    result := X11_ThreadID;
  {$ENDIF}
  {$IFDEF DARWIN}
    result := Cocoa_ThreadID;
  {$ENDIF}
end;

function GLPT_RunThread(thread: pGLPT_Thread): pointer; cdecl;
begin
  thread^.id := GLPT_ThreadID;
  thread^.status := thread^.start(thread^.userData);
  result := nil;
end;

function GLPT_CreateThread(start: GLPT_ThreadFunction; name: string = ''; userData: pointer = nil; stacksize: integer = GLPT_THREAD_DEFAULT_STACK_SIZE): pGLPT_Thread;
var
  success: boolean;
  thread: pGLPT_Thread;
begin
  thread := pGLPT_Thread(calloc(sizeof(GLPT_Thread)));
  thread^.start := start;
  thread^.name := name;
  thread^.userData := userData;
  thread^.status := -1;
  thread^.stacksize := stacksize;

  {$IFDEF MSWINDOWS}
    success := gdi_CreateThread(thread);
  {$ENDIF}
  {$IFDEF LINUX}
    success := X11_CreateThread(thread);
  {$ENDIF}
  {$IFDEF DARWIN}
    success := Cocoa_CreateThread(thread);
  {$ENDIF}

  if success then
    result := thread
  else
    begin
      FreeMem(thread);
      result := nil;
    end;
end;

procedure GLPT_DetachThread(thread: pGLPT_Thread);
begin
  if thread = nil then
    exit;
  {$IFDEF MSWINDOWS}
    gdi_DetachThread(thread);
  {$ENDIF}
  {$IFDEF LINUX}
    X11_DetachThread(thread);
  {$ENDIF}
  {$IFDEF DARWIN}
    Cocoa_DetachThread(thread);
  {$ENDIF}
end;

procedure GLPT_WaitThread(var thread: pGLPT_Thread; var status: integer);
begin
  if assigned(thread) then
    begin
      {$IFDEF MSWINDOWS}
        gdi_WaitThread(thread);
      {$ENDIF}
      {$IFDEF LINUX}
        X11_WaitThread(thread);
      {$ENDIF}
      {$IFDEF DARWIN}
        Cocoa_WaitThread(thread);
      {$ENDIF}
      status := thread^.status;
      FreeMem(thread);
      thread := nil;
    end;
end;

begin
  // init FPC heap manager
  TThread.Create(false).WaitFor;
end.
