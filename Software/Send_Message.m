function [MsgtoSend] = Send_Message(Msg,Z1,Z2,Z3,Z4)
disp(Msg)
% Byte 0:
Msg1 = floor(Msg/16);
Msg1 = Msg1 + 128;
byte0 = Msg1;
% Byte 1:
Msg2 = bitand(Msg,15);
byte1 = Msg2;
% Byte 2:
byte2 = Z1*8 + Z2; 
% Byte 3:
byte3 = Z3*8 + Z4;
% Combinando todos los bytes de la trama
MsgtoSend = [byte0,byte1,byte2,byte3];
disp(MsgtoSend)
end