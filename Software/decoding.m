%% Funcion decodificacion y conversión de datos obtenidos del puerto serial

function [AngleSC, LidarSC, SonarSC] = decoding(valorADC)
databytes = int8(valorADC);                           % Tipo de datos
start = find(databytes > 0,1);                        % Sync
synceddata = databytes(start:end-mod((16-start),4)-1);
synceddata = typecast(synceddata,'uint8');
blocksize = length(synceddata)/4;                     % Tamaño de cada bloque
byte1 = synceddata(1:4:end);
byte2 = synceddata(2:4:end);
byte3 = synceddata(3:4:end);
byte4 = synceddata(4:4:end); 
mask_pos1(1:blocksize,1) = uint8(127);                % Creando máscaras para asignación a las variables
mask_sonar1(1:blocksize,1) = uint8(127);
mask_sonar2(1:blocksize,1) = uint8(96);
mask_lidar1(1:blocksize,1) = uint8(31);
mask_lidar2(1:blocksize,1) = uint8(127);
AngleSC = bitand(byte1, mask_pos1);                   % Asignación de posición (ángulo)
AngleSC = single(AngleSC);
AngleSC = round(AngleSC,1);
sonar1 = single(bitand(byte2, mask_sonar1));          % Agregando máscaras y asignándolas a Sonar y Lidar
sonar2 = single(bitand(byte3, mask_sonar2));
lidar1 = single(bitand(byte3, mask_lidar1));
lidar2 = single(bitand(byte4, mask_lidar2));
SonarSC = sonar1*4 + sonar2/32;
LidarSC = lidar1*128 + lidar2;
end
