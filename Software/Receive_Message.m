function [Msg_Rec] = Receive_Message(DataMsg)
disp(DataMsg)
%Decodificacion de la trama
databytes = uint8(DataMsg);                              
byte1 = databytes(1);
byte2 = databytes(2);
% Máscara de byte
mask_msg(1) = uint8(15);                
% Asignaciones para el mensaje
Msg1 = (bitand(byte1,mask_msg))*16;
Msg2 = bitand(byte2, mask_msg);
Msg_Rec = Msg1 + Msg2;
disp(Msg_Rec)
end