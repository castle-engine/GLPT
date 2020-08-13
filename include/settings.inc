{$IFDEF DARWIN}
  {$define COCOA}
{$ENDIF}

{$IF defined(CPUARM) or defined(CPUAARCH64)}
  {$define IPHONE}
  {$undef COCOA}
{$ENDIF}

{$IFDEF IPHONESIM}
  {$define IPHONE}
  {$undef COCOA}
{$ENDIF}

{$IFDEF COCOA}
  {$modeswitch advancedrecords}
  {$modeswitch objectivec2}
  {$linkframework CoreVideo}
{$ENDIF}

{$IFDEF IPHONE}
  {$modeswitch advancedrecords}
  {$modeswitch objectivec2}
{$ENDIF}