

// https://stackoverflow.com/questions/2234364/how-to-detect-a-gamepad-button-press-on-osx-10-5-and-higher

var
  HIDElementDeviceID: integer = 0;

type
  HIDElementType = (hid_element_hat, hid_element_axis, hid_element_button);
  HIDElementInfo = class
    typ: HIDElementType;
    ref: IOHIDElementRef;
    cookie: IOHIDElementCookie;
    usagePage: UInt32;
    usage: UInt32;
    min: SInt32;
    max: SInt32;
    mid: SInt32;
    index: UInt16;
    minReport: cint32;
    maxReport: cint32;
    deviceID: integer;
    constructor Create(_type: HIDElementType);
  end;
  HIDElementHat = class (HIDElementInfo)
    value: array[0..127] of SInt32;
  end;
  HIDElementAxis = class (HIDElementInfo)
    value: array[0..127] of SInt32;
  end;
  HIDElementButton = class (HIDElementInfo)
    value: array[0..127] of SInt32;
  end;
  HIDElementInfoList = specialize TFPGObjectList<HIDElementInfo>;

constructor HIDElementInfo.Create(_type: HIDElementType);
begin
  typ := _type;
end;

// TODO: this information needs to be in the GLPT_MessageParams I think but not for now
type
  HIDDeviceInfo = class
    name: string;
    guid: array[0..1] of UInt8;
    hidDevice: IOHIDDeviceRef;
    usagePage: SInt32;
    usage: SInt32;
    elements: HIDElementInfoList;
    elementIndexes: array[HIDElementType] of UInt16;
    id: integer;

    constructor Create;
    procedure AfterConstruction; override;
    destructor Destroy; override;
  end;
  HIDDeviceInfoList = specialize TFPGObjectList<HIDDeviceInfo>;

constructor HIDDeviceInfo.Create;
begin
  id := HIDElementDeviceID;
  inc(HIDElementDeviceID);
end;

procedure HIDDeviceInfo.AfterConstruction;
begin
  elements := HIDElementInfoList.Create;
end;

destructor HIDDeviceInfo.Destroy;
begin
  elements.Free;
end;

var
  RegisteredHIDDevices: HIDDeviceInfoList = nil;

function Cocoa_GetHIDDeviceInfo(hidDevice: IOHIDDeviceRef; var info: HIDDeviceInfo): boolean;
  
  function ElementAlreadyAdded(cookie: IOHIDElementCookie; device: HIDDeviceInfo): boolean;
  var
    element: HIDElementInfo;
  begin
    for pointer(element) in device.elements do
      begin
        if element.cookie = cookie then
          exit(true);
      end;
    result := false;
  end;

  procedure AddHIDElement(elementRef: IOHIDElementRef; device: HIDDeviceInfo);
  var
    usagePage: integer;
    usage: integer;
    cookie: IOHIDElementCookie;
    element: HIDElementInfo;
    children: NSArray;
    child: IOHIDElementRef;
  begin
    usagePage := IOHIDElementGetUsagePage(elementRef);
    usage := IOHIDElementGetUsage(elementRef);
    cookie := IOHIDElementGetCookie(elementRef);
    element := nil;

    case IOHIDElementGetType(elementRef) of
      kIOHIDElementTypeInput_Misc,
      kIOHIDElementTypeInput_Button,
      kIOHIDElementTypeInput_Axis:
        begin
          case usagePage of
            kHIDPage_GenericDesktop:
              begin
                case usage of
                  kHIDUsage_GD_X,
                  kHIDUsage_GD_Y,
                  kHIDUsage_GD_Z,
                  kHIDUsage_GD_Rx,
                  kHIDUsage_GD_Ry,
                  kHIDUsage_GD_Rz,
                  kHIDUsage_GD_Slider,
                  kHIDUsage_GD_Dial,
                  kHIDUsage_GD_Wheel:
                    begin
                      // add axes
                      if not ElementAlreadyAdded(cookie, device) then
                        element := HIDElementAxis.Create(hid_element_axis);
                    end;
                  kHIDUsage_GD_Hatswitch:
                    begin
                      // add hats 
                      if not ElementAlreadyAdded(cookie, device) then
                        element := HIDElementHat.Create(hid_element_hat);
                    end;
                  kHIDUsage_GD_DPadUp,
                  kHIDUsage_GD_DPadDown,
                  kHIDUsage_GD_DPadRight,
                  kHIDUsage_GD_DPadLeft,
                  kHIDUsage_GD_Start,
                  kHIDUsage_GD_Select:
                    begin
                      // add buttons
                      if not ElementAlreadyAdded(cookie, device) then
                        element := HIDElementButton.Create(hid_element_button);
                    end;
                end;
              end;
            kHIDPage_Simulation:
              begin
                case usage of
                  kHIDUsage_Sim_Rudder,
                  kHIDUsage_Sim_Throttle:
                    begin
                      // add axes
                      if not ElementAlreadyAdded(cookie, device) then
                        element := HIDElementAxis.Create(hid_element_axis);
                    end;
                end;
              end;
            kHIDPage_Button,
            kHIDPage_Consumer:
              begin
                // e.g. 'pause' button on Steelseries MFi gamepads
                if not ElementAlreadyAdded(cookie, device) then
                  element := HIDElementButton.Create(hid_element_button);
              end;
            otherwise
              ;
          end;
        end;

      kIOHIDElementTypeCollection:
        begin
          children := NSArray(IOHIDElementGetChildren(elementRef));
          if assigned(children) then
            for pointer(child) in children do
              AddHIDElement(child, device);
          exit;
        end;
      end;

    // add element to device
    if assigned(element) then
      begin
        element.deviceID := device.id;
        element.ref := elementRef;
        element.usagePage := usagePage;
        element.usage := usage;
        element.min := IOHIDElementGetLogicalMin(elementRef);
        element.max := IOHIDElementGetLogicalMax(elementRef);
        element.mid := round(element.max / 2);
        element.cookie := IOHIDElementGetCookie(elementRef);
        
        element.index := device.elementIndexes[element.typ];
        inc(device.elementIndexes[element.typ]);

        //writeln('  type: ', element.typ);
        //writeln('  min: ', element.min);
        //writeln('  mid: ', element.mid);
        //writeln('  max: ', element.max);
        device.elements.Add(element);
      end;
  end;

var
  ref: CFTypeRef;
  elements: CFArrayRef;
  element: IOHIDElementRef;
begin
  info := HIDDeviceInfo.Create;

  ref := IOHIDDeviceGetProperty(hidDevice, CFSTR(kIOHIDPrimaryUsagePageKey));
  if assigned(ref) then
    CFNumberGetValue(ref, kCFNumberSInt32Type, @info.usagePage);
  
  ref := IOHIDDeviceGetProperty(hidDevice, CFSTR(kIOHIDPrimaryUsageKey));
  if assigned(ref) then
    CFNumberGetValue(ref, kCFNumberSInt32Type, @info.usage);

  // TODO: we're only looking for gamepads?
  if (info.usage <> kHIDUsage_GD_Joystick) and 
     (info.usage <> kHIDUsage_GD_GamePad) and 
     (info.usage <> kHIDUsage_GD_MultiAxisController) then
    begin
      info.Free;
      exit(false);
    end;

  info.hidDevice := hidDevice;

  // get device name
  ref := IOHIDDeviceGetProperty(hidDevice, CFSTR(kIOHIDProductKey));
  if not assigned(ref) then
     ref := IOHIDDeviceGetProperty(hidDevice, CFSTR(kIOHIDManufacturerKey));

  if assigned(ref) then
    CFStringGetPascalString(ref, @info.name, sizeof(info.name), kCFStringEncodingUTF8)
  else
    info.name := 'Unidentified device';

  ref := IOHIDDeviceGetProperty(hidDevice, CFSTR(kIOHIDVendorIDKey));
  if assigned(ref) then
    CFNumberGetValue(ref, kCFNumberSInt32Type, @info.guid[0]);
  
  ref := IOHIDDeviceGetProperty(hidDevice, CFSTR(kIOHIDProductIDKey));
  if assigned(ref) then
    CFNumberGetValue(ref, kCFNumberSInt32Type, @info.guid[1]);

  // TODO: make a final effort to get a proper guid
  ///* Check to make sure we have a vendor and product ID
  //   If we don't, use the same algorithm as the Linux code for Bluetooth devices */
  //guid32 = (Uint32*)pDevice->guid.data;
  //if (!guid32[0] && !guid32[1]) {
  //    /* If we don't have a vendor and product ID this is probably a Bluetooth device */
  //    const Uint16 BUS_BLUETOOTH = 0x05;
  //    Uint16 *guid16 = (Uint16 *)guid32;
  //    *guid16++ = BUS_BLUETOOTH;
  //    *guid16++ = 0;
  //    SDL_strlcpy((char*)guid16, pDevice->product, sizeof(pDevice->guid.data) - 4);
  //}

  elements := IOHIDDeviceCopyMatchingElements(hidDevice, nil, kIOHIDOptionsTypeNone);
  if assigned(elements) then
    begin
      for pointer(element) in NSArray(elements) do
        AddHIDElement(element, info);
      CFRelease(elements);
    end;

  result := true;
end;

procedure Cocoa_GamepadWasAddedCallback(context: pointer; result_: IOKit.IOReturn; sender: pointer; device: IOHIDDeviceRef); cdecl;
var
  info: HIDDeviceInfo;
  params: GLPT_MessageParams;
begin
  FillChar(params, sizeof(params), 0);
  glptPostMessage(nil, GLPT_MESSAGE_CONTROLLER_ADDED, params);      

  if Cocoa_GetHIDDeviceInfo(device, info) then
    begin
      if RegisteredHIDDevices = nil then
        RegisteredHIDDevices := HIDDeviceInfoList.Create;
      RegisteredHIDDevices.Add(info);
    end;
end;

procedure Cocoa_GamepadWasRemovedCallback(context: pointer; result_: IOKit.IOReturn; sender: pointer; device: IOHIDDeviceRef); cdecl;
var
  i: integer;
  params: GLPT_MessageParams;
begin
  FillChar(params, sizeof(params), 0);
  glptPostMessage(nil, GLPT_MESSAGE_CONTROLLER_REMOVED, params);      

  for i := 0 to RegisteredHIDDevices.Count - 1 do
    if HIDDeviceInfo(RegisteredHIDDevices[i]).hidDevice = device then
      begin
        RegisteredHIDDevices.Delete(i);
        break;    
      end;
end;

{ note: keeping for testing right now }
procedure Cocoa_GamepadActionCallback(context: pointer; result_: IOReturn; sender: pointer; value: IOHIDValueRef); cdecl;
var
  element: IOHIDElementRef;
  usagePage: integer;
  usage: integer;
begin
  element := IOHIDValueGetElement(value);
  writeln('gamepad value: ', IOHIDValueGetIntegerValue(value));
  usagePage := IOHIDElementGetUsagePage(element);
  usage := IOHIDElementGetUsage(element);
  writeln('usagePage: ', usagePage);
  writeln('usage: ', usage);
  writeln('type: ', IOHIDElementGetType(element));
end;

procedure Cocoa_PollDevices;
  
  function GetHIDElementState(device: HIDDeviceInfo; element: HIDElementInfo): SInt32;
  var
    valueRef: IOHIDValueRef;
  begin
    result := 0;
    if IOHIDDeviceGetValue(device.hidDevice, element.ref, @valueRef) = kIOReturnSuccess then
      begin
        result := IOHIDValueGetIntegerValue(valueRef);
        // reported min/max values for auto-calibration
        if result < element.minReport then
          element.minReport := result;
        if result > element.maxReport then
          element.maxReport := result;
      end
    else
      result := 0;
  end;

  function GetHIDScaledCalibratedState(device: HIDDeviceInfo; element: HIDElementInfo; min, max: SInt32): SInt32;
  var
    deviceScale: single;
    readScale: single;
    value: SInt32;
  begin
    deviceScale := max - min;
    readScale := element.maxReport - element.minReport;
    value := GetHIDElementState(device, element);
    // no scaling at all
    if readScale = 0 then
      exit(value);
    result := trunc(((value - element.minReport) * deviceScale / readScale) + min);
  end;


  procedure UpdateController(device: HIDDeviceInfo; element: HIDElementInfo);
  const
    AXIS_CALIBRATED_MIN = -32768;
    AXIS_CALIBRATED_MAX = 32767;
  var
    usage: integer;
    value: integer;
    axis: HIDElementAxis;
    button: HIDElementButton;
    hat: HIDElementHat;
    params: GLPT_MessageParams;
    windowRef: pGLPTwindow;
  begin
    usage := IOHIDElementGetUsage(element.ref);

    if assigned(NSApp.keyWindow) then
      windowRef := pGLPTwindow(NSApp.keyWindow.performSelector_withObject(objcselector('glptWindowRef'), nil))
    else
      windowRef := nil;

    writeln(element.typ);
    case element.typ of
      hid_element_axis:
        begin
          // TODO: don't send event for initial value
          value := GetHIDScaledCalibratedState(device, element, AXIS_CALIBRATED_MIN, AXIS_CALIBRATED_MAX);
          axis := HIDElementAxis(element);
          if (axis.value[usage] <> value) then
            begin
              //writeln('axis ',axis.index,' value: ', value);
              params.axis.which := device.id;
              params.axis.axis := axis.index;
              params.axis.value := value;
              if assigned(windowRef) then
                glptPostMessage(windowRef, GLPT_MESSAGE_CONTROLLER_AXIS, params);      
            end;
          axis.value[usage] := value;
        end;
      hid_element_button:
        begin
          value := GetHIDElementState(device, element);
          button := HIDElementButton(element);
          if (button.value[usage] <> value) then
            begin
              //writeln('button ',button.index,' value: ', value);              
              params.button.which := device.id;
              params.button.button := button.index;
              params.button.state := value;
              if assigned(windowRef) then
                glptPostMessage(windowRef, GLPT_MESSAGE_CONTROLLER_BUTTON, params);      
            end;
          button.value[usage] := value;
        end;
      hid_element_hat:
        begin
          // TODO: implement joysticks but I don't have any for testing
          glptError(GLPT_ERROR_PLATFORM, 'HIDElementHat is not yet implemetented in Cocoa.', true);
          //hat := HIDElementHat(element);
          //if (hat.value[usage] <> value) then
          //  begin
          //    writeln('hat ',hat.index,' value: ', value);
          //  end;
          //hat.value[usage] := value;
        end;
    end;
  end;

var
  device: HIDDeviceInfo;
  element: HIDElementInfo;
begin
  writeln('RegisteredHIDDevices:',assigned(RegisteredHIDDevices));
  if RegisteredHIDDevices = nil then
    exit;
  for device in RegisteredHIDDevices do
    for element in device.elements do
      UpdateController(device, element);
end;

var
  HIDManager: IOHIDManagerRef = nil;

function Cocoa_Gamepad_Init: boolean;

  function CreateHIDDeviceMatchDictionary(page: integer; usage: integer): NSMutableDictionary;
  begin
    result := NSMutableDictionary.dictionaryWithCapacity(2);
    result.setObject_forKey(NSNumber.numberWithInt(page), NSSTR(kIOHIDDeviceUsagePageKey));
    result.setObject_forKey(NSNumber.numberWithInt(usage), NSSTR(kIOHIDDeviceUsageKey));
  end;

var
  matches: NSMutableArray;
begin

  // criteria
  matches := NSMutableArray.alloc.init.autorelease;
  //matches.addObject(CreateHIDDeviceMatchDictionary(kHIDPage_GenericDesktop, kHIDUsage_GD_Joystick));
  matches.addObject(CreateHIDDeviceMatchDictionary(kHIDPage_GenericDesktop, kHIDUsage_GD_GamePad));
  matches.addObject(CreateHIDDeviceMatchDictionary(kHIDPage_GenericDesktop, kHIDUsage_GD_MultiAxisController));

  HIDManager := IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);
  if HIDManager = nil then
    begin
      glptError(GLPT_ERROR_PLATFORM, 'IOHIDManagerCreate failed.');
      exit(false);
    end;

  if IOHIDManagerOpen(HIDManager, kIOHIDOptionsTypeNone) <> kIOReturnSuccess then
    begin
      glptError(GLPT_ERROR_PLATFORM, 'IOHIDManagerOpen failed.');
      exit(false);
    end;

  IOHIDManagerSetDeviceMatchingMultiple(HIDManager, CFArrayRef(matches));
  IOHIDManagerRegisterDeviceMatchingCallback(HIDManager, @Cocoa_GamepadWasAddedCallback, nil);
  IOHIDManagerRegisterDeviceRemovalCallback(HIDManager, @Cocoa_GamepadWasRemovedCallback, nil);
  //IOHIDManagerRegisterInputValueCallback(HIDManager, @Cocoa_GamepadActionCallback, nil);

  IOHIDManagerScheduleWithRunLoop(HIDManager, CFRunLoopGetCurrent, kCFRunLoopDefaultMode);

  result := true;
  // what is this for in sdl?
  //while (CFRunLoopRunInMode(SDL_JOYSTICK_RUNLOOP_MODE,0,TRUE) == kCFRunLoopRunHandledSource) {
  //    /* no-op. Callback fires once per existing device. */
  //}
end;
