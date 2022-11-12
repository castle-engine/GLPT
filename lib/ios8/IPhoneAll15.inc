
type
  UIKeyboardHIDUsage = CFIndex { unavailable in watchos } { available in ios 13.4, tvos 13.4 };
  UIKeyboardHIDUsagePtr = ^UIKeyboardHIDUsage { unavailable in watchos } { available in ios 13.4, tvos 13.4 };

const
  UIKeyboardHIDUsageKeyboardErrorRollOver = $01;
  UIKeyboardHIDUsageKeyboardPOSTFail = $02;
  UIKeyboardHIDUsageKeyboardErrorUndefined = $03;
  UIKeyboardHIDUsageKeyboardA = $04;
  UIKeyboardHIDUsageKeyboardB = $05;
  UIKeyboardHIDUsageKeyboardC = $06;
  UIKeyboardHIDUsageKeyboardD = $07;
  UIKeyboardHIDUsageKeyboardE = $08;
  UIKeyboardHIDUsageKeyboardF = $09;
  UIKeyboardHIDUsageKeyboardG = $0A;
  UIKeyboardHIDUsageKeyboardH = $0B;
  UIKeyboardHIDUsageKeyboardI = $0C;
  UIKeyboardHIDUsageKeyboardJ = $0D;
  UIKeyboardHIDUsageKeyboardK = $0E;
  UIKeyboardHIDUsageKeyboardL = $0F;
  UIKeyboardHIDUsageKeyboardM = $10;
  UIKeyboardHIDUsageKeyboardN = $11;
  UIKeyboardHIDUsageKeyboardO = $12;
  UIKeyboardHIDUsageKeyboardP = $13;
  UIKeyboardHIDUsageKeyboardQ = $14;
  UIKeyboardHIDUsageKeyboardR = $15;
  UIKeyboardHIDUsageKeyboardS = $16;
  UIKeyboardHIDUsageKeyboardT = $17;
  UIKeyboardHIDUsageKeyboardU = $18;
  UIKeyboardHIDUsageKeyboardV = $19;
  UIKeyboardHIDUsageKeyboardW = $1A;
  UIKeyboardHIDUsageKeyboardX = $1B;
  UIKeyboardHIDUsageKeyboardY = $1C;
  UIKeyboardHIDUsageKeyboardZ = $1D;
  UIKeyboardHIDUsageKeyboard1 = $1E;
  UIKeyboardHIDUsageKeyboard2 = $1F;
  UIKeyboardHIDUsageKeyboard3 = $20;
  UIKeyboardHIDUsageKeyboard4 = $21;
  UIKeyboardHIDUsageKeyboard5 = $22;
  UIKeyboardHIDUsageKeyboard6 = $23;
  UIKeyboardHIDUsageKeyboard7 = $24;
  UIKeyboardHIDUsageKeyboard8 = $25;
  UIKeyboardHIDUsageKeyboard9 = $26;
  UIKeyboardHIDUsageKeyboard0 = $27;
  UIKeyboardHIDUsageKeyboardReturnOrEnter = $28;
  UIKeyboardHIDUsageKeyboardEscape = $29;
  UIKeyboardHIDUsageKeyboardDeleteOrBackspace = $2A;
  UIKeyboardHIDUsageKeyboardTab = $2B;
  UIKeyboardHIDUsageKeyboardSpacebar = $2C;
  UIKeyboardHIDUsageKeyboardHyphen = $2D;
  UIKeyboardHIDUsageKeyboardEqualSign = $2E;
  UIKeyboardHIDUsageKeyboardOpenBracket = $2F;
  UIKeyboardHIDUsageKeyboardCloseBracket = $30;
  UIKeyboardHIDUsageKeyboardBackslash = $31;
  UIKeyboardHIDUsageKeyboardNonUSPound = $32;
  UIKeyboardHIDUsageKeyboardSemicolon = $33;
  UIKeyboardHIDUsageKeyboardQuote = $34;
  UIKeyboardHIDUsageKeyboardGraveAccentAndTilde = $35;
  UIKeyboardHIDUsageKeyboardComma = $36;
  UIKeyboardHIDUsageKeyboardPeriod = $37;
  UIKeyboardHIDUsageKeyboardSlash = $38;
  UIKeyboardHIDUsageKeyboardCapsLock = $39;
  UIKeyboardHIDUsageKeyboardF1 = $3A;
  UIKeyboardHIDUsageKeyboardF2 = $3B;
  UIKeyboardHIDUsageKeyboardF3 = $3C;
  UIKeyboardHIDUsageKeyboardF4 = $3D;
  UIKeyboardHIDUsageKeyboardF5 = $3E;
  UIKeyboardHIDUsageKeyboardF6 = $3F;
  UIKeyboardHIDUsageKeyboardF7 = $40;
  UIKeyboardHIDUsageKeyboardF8 = $41;
  UIKeyboardHIDUsageKeyboardF9 = $42;
  UIKeyboardHIDUsageKeyboardF10 = $43;
  UIKeyboardHIDUsageKeyboardF11 = $44;
  UIKeyboardHIDUsageKeyboardF12 = $45;
  UIKeyboardHIDUsageKeyboardPrintScreen = $46;
  UIKeyboardHIDUsageKeyboardScrollLock = $47;
  UIKeyboardHIDUsageKeyboardPause = $48;
  UIKeyboardHIDUsageKeyboardInsert = $49;
  UIKeyboardHIDUsageKeyboardHome = $4A;
  UIKeyboardHIDUsageKeyboardPageUp = $4B;
  UIKeyboardHIDUsageKeyboardDeleteForward = $4C;
  UIKeyboardHIDUsageKeyboardEnd = $4D;
  UIKeyboardHIDUsageKeyboardPageDown = $4E;
  UIKeyboardHIDUsageKeyboardRightArrow = $4F;
  UIKeyboardHIDUsageKeyboardLeftArrow = $50;
  UIKeyboardHIDUsageKeyboardDownArrow = $51;
  UIKeyboardHIDUsageKeyboardUpArrow = $52;
  UIKeyboardHIDUsageKeypadNumLock = $53;
  UIKeyboardHIDUsageKeypadSlash = $54;
  UIKeyboardHIDUsageKeypadAsterisk = $55;
  UIKeyboardHIDUsageKeypadHyphen = $56;
  UIKeyboardHIDUsageKeypadPlus = $57;
  UIKeyboardHIDUsageKeypadEnter = $58;
  UIKeyboardHIDUsageKeypad1 = $59;
  UIKeyboardHIDUsageKeypad2 = $5A;
  UIKeyboardHIDUsageKeypad3 = $5B;
  UIKeyboardHIDUsageKeypad4 = $5C;
  UIKeyboardHIDUsageKeypad5 = $5D;
  UIKeyboardHIDUsageKeypad6 = $5E;
  UIKeyboardHIDUsageKeypad7 = $5F;
  UIKeyboardHIDUsageKeypad8 = $60;
  UIKeyboardHIDUsageKeypad9 = $61;
  UIKeyboardHIDUsageKeypad0 = $62;
  UIKeyboardHIDUsageKeypadPeriod = $63;
  UIKeyboardHIDUsageKeyboardNonUSBackslash = $64;
  UIKeyboardHIDUsageKeyboardApplication = $65;
  UIKeyboardHIDUsageKeyboardPower = $66;
  UIKeyboardHIDUsageKeypadEqualSign = $67;
  UIKeyboardHIDUsageKeyboardF13 = $68;
  UIKeyboardHIDUsageKeyboardF14 = $69;
  UIKeyboardHIDUsageKeyboardF15 = $6A;
  UIKeyboardHIDUsageKeyboardF16 = $6B;
  UIKeyboardHIDUsageKeyboardF17 = $6C;
  UIKeyboardHIDUsageKeyboardF18 = $6D;
  UIKeyboardHIDUsageKeyboardF19 = $6E;
  UIKeyboardHIDUsageKeyboardF20 = $6F;
  UIKeyboardHIDUsageKeyboardF21 = $70;
  UIKeyboardHIDUsageKeyboardF22 = $71;
  UIKeyboardHIDUsageKeyboardF23 = $72;
  UIKeyboardHIDUsageKeyboardF24 = $73;
  UIKeyboardHIDUsageKeyboardExecute = $74;
  UIKeyboardHIDUsageKeyboardHelp = $75;
  UIKeyboardHIDUsageKeyboardMenu = $76;
  UIKeyboardHIDUsageKeyboardSelect = $77;
  UIKeyboardHIDUsageKeyboardStop = $78;
  UIKeyboardHIDUsageKeyboardAgain = $79;
  UIKeyboardHIDUsageKeyboardUndo = $7A;
  UIKeyboardHIDUsageKeyboardCut = $7B;
  UIKeyboardHIDUsageKeyboardCopy = $7C;
  UIKeyboardHIDUsageKeyboardPaste = $7D;
  UIKeyboardHIDUsageKeyboardFind = $7E;
  UIKeyboardHIDUsageKeyboardMute = $7F;
  UIKeyboardHIDUsageKeyboardVolumeUp = $80;
  UIKeyboardHIDUsageKeyboardVolumeDown = $81;
  UIKeyboardHIDUsageKeyboardLockingCapsLock = $82;
  UIKeyboardHIDUsageKeyboardLockingNumLock = $83;
  UIKeyboardHIDUsageKeyboardLockingScrollLock = $84;
  UIKeyboardHIDUsageKeypadComma = $85;
  UIKeyboardHIDUsageKeypadEqualSignAS400 = $86;
  UIKeyboardHIDUsageKeyboardInternational1 = $87;
  UIKeyboardHIDUsageKeyboardInternational2 = $88;
  UIKeyboardHIDUsageKeyboardInternational3 = $89;
  UIKeyboardHIDUsageKeyboardInternational4 = $8A;
  UIKeyboardHIDUsageKeyboardInternational5 = $8B;
  UIKeyboardHIDUsageKeyboardInternational6 = $8C;
  UIKeyboardHIDUsageKeyboardInternational7 = $8D;
  UIKeyboardHIDUsageKeyboardInternational8 = $8E;
  UIKeyboardHIDUsageKeyboardInternational9 = $8F;
  UIKeyboardHIDUsageKeyboardLANG1 = $90;
  UIKeyboardHIDUsageKeyboardLANG2 = $91;
  UIKeyboardHIDUsageKeyboardLANG3 = $92;
  UIKeyboardHIDUsageKeyboardLANG4 = $93;
  UIKeyboardHIDUsageKeyboardLANG5 = $94;
  UIKeyboardHIDUsageKeyboardLANG6 = $95;
  UIKeyboardHIDUsageKeyboardLANG7 = $96;
  UIKeyboardHIDUsageKeyboardLANG8 = $97;
  UIKeyboardHIDUsageKeyboardLANG9 = $98;
  UIKeyboardHIDUsageKeyboardAlternateErase = $99;
  UIKeyboardHIDUsageKeyboardSysReqOrAttention = $9A;
  UIKeyboardHIDUsageKeyboardCancel = $9B;
  UIKeyboardHIDUsageKeyboardClear = $9C;
  UIKeyboardHIDUsageKeyboardPrior = $9D;
  UIKeyboardHIDUsageKeyboardReturn = $9E;
  UIKeyboardHIDUsageKeyboardSeparator = $9F;
  UIKeyboardHIDUsageKeyboardOut = $A0;
  UIKeyboardHIDUsageKeyboardOper = $A1;
  UIKeyboardHIDUsageKeyboardClearOrAgain = $A2;
  UIKeyboardHIDUsageKeyboardCrSelOrProps = $A3;
  UIKeyboardHIDUsageKeyboardExSel = $A4;
  UIKeyboardHIDUsageKeyboardLeftControl = $E0;
  UIKeyboardHIDUsageKeyboardLeftShift = $E1;
  UIKeyboardHIDUsageKeyboardLeftAlt = $E2;
  UIKeyboardHIDUsageKeyboardLeftGUI = $E3;
  UIKeyboardHIDUsageKeyboardRightControl = $E4;
  UIKeyboardHIDUsageKeyboardRightShift = $E5;
  UIKeyboardHIDUsageKeyboardRightAlt = $E6;
  UIKeyboardHIDUsageKeyboardRightGUI = $E7;
  UIKeyboardHIDUsageKeyboard_Reserved = $FFFF;
  UIKeyboardHIDUsageKeyboardHangul = UIKeyboardHIDUsageKeyboardLANG1;
  UIKeyboardHIDUsageKeyboardHanja = UIKeyboardHIDUsageKeyboardLANG2;
  UIKeyboardHIDUsageKeyboardKanaSwitch = UIKeyboardHIDUsageKeyboardLANG1;
  UIKeyboardHIDUsageKeyboardAlphanumericSwitch = UIKeyboardHIDUsageKeyboardLANG2;
  UIKeyboardHIDUsageKeyboardKatakana = UIKeyboardHIDUsageKeyboardLANG3;
  UIKeyboardHIDUsageKeyboardHiragana = UIKeyboardHIDUsageKeyboardLANG4;
  UIKeyboardHIDUsageKeyboardZenkakuHankakuKanji = UIKeyboardHIDUsageKeyboardLANG5;

type
  UIPressPhase = NSInteger { available in ios 9.0 };
  UIPressPhasePtr = ^UIPressPhase { available in ios 9.0 };

const
  UIPressPhaseBegan = 0;
  UIPressPhaseChanged = 1;
  UIPressPhaseStationary = 2;
  UIPressPhaseEnded = 3;
  UIPressPhaseCancelled = 4;

type
  UIPressType = NSInteger { available in ios 9.0 };
  UIPressTypePtr = ^UIPressType { available in ios 9.0 };

const
  UIPressTypeUpArrow = 0;
  UIPressTypeDownArrow = 1;
  UIPressTypeLeftArrow = 2;
  UIPressTypeRightArrow = 3;
  UIPressTypeSelect = 4;
  UIPressTypeMenu = 5;
  UIPressTypePlayPause = 6;
  UIPressTypePageUp = 30 { unavailable in ios, watchos } { available in tvos 14.3 };
  UIPressTypePageDown = 31 { unavailable in ios, watchos } { available in tvos 14.3 };

type
  UIKey = objcclass external (NSObject, NSCopyingProtocol, NSCodingProtocol)
  public
    function characters: NSString; message 'characters';
    function charactersIgnoringModifiers: NSString; message 'charactersIgnoringModifiers';
    function modifierFlags: UIKeyModifierFlags; message 'modifierFlags';
    function keyCode: UIKeyboardHIDUsage; message 'keyCode';

    { Adopted protocols }
    function copyWithZone (zone_: NSZonePtr): id; message 'copyWithZone:';
    procedure encodeWithCoder (coder: NSCoder); message 'encodeWithCoder:';
    function initWithCoder (coder: NSCoder): id; message 'initWithCoder:';
  end;

type
  UIPress = objcclass external (NSObject)
  public
    function timestamp: NSTimeInterval; message 'timestamp';
    function phase: UIPressPhase; message 'phase';
    function type_: UIPressType; message 'type';
    function window: UIWindow; message 'window';
    function responder: UIResponder; message 'responder';
    function gestureRecognizers: NSArray; message 'gestureRecognizers';
    function force: CGFloat; message 'force';
    function key: UIKey; message 'key';
  end;

type
  UIPressesEvent = objcclass external (UIEvent)
  public
    function allPresses: NSSet; message 'allPresses';
    function pressesForGestureRecognizer (gesture: UIGestureRecognizer): NSSet; message 'pressesForGestureRecognizer:';
  end;

type
  UIResponder_Additions = objccategory external (UIResponder)
    { Added in iOS 9 }
    procedure pressesBegan_withEvent (presses: NSSet; event: UIPressesEvent); message 'pressesBegan:withEvent:'; { available in ios 9.0 }
    procedure pressesChanged_withEvent (presses: NSSet; event: UIPressesEvent); message 'pressesChanged:withEvent:'; { available in ios 9.0 }
    procedure pressesEnded_withEvent (presses: NSSet; event: UIPressesEvent); message 'pressesEnded:withEvent:'; { available in ios 9.0 }
    procedure pressesCancelled_withEvent (presses: NSSet; event: UIPressesEvent); message 'pressesCancelled:withEvent:'; { available in ios 9.0 }
  end;

type
  UITouch_Additions = objccategory external (UITouch)
    { Added in iOS 9 }
    function force: CGFloat; message 'force';
  end;

type
  NSFileManager_Additions = objccategory external (NSFileManager)
    function createDirectoryAtURL_withIntermediateDirectories_attributes_error (url: NSURL; createIntermediates: boolean; attributes: NSDictionary; error: NSErrorPtr): boolean; message 'createDirectoryAtURL:withIntermediateDirectories:attributes:error:'; { available in 10_7, 5_0 }
  end;