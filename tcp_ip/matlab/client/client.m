%% TCP/IP client
%
% Author: Alexandre Lopes
% Date:   24.07.2015

% variables
IP_ADDRESS = 'localhost';
PORT       = 59263;
TIMEOUT    = 5;

% connect to server
t = tcpip(IP_ADDRESS, PORT, 'NetworkRole', 'client');
fopen(t);
disp('Successfully connected to the server.')

reply = '';
data_rec = [];


% send data to server
while 1

    data = input('>', 's');

    % Write data to server
    fwrite(t, data);
   
    if strcmp(data, 'quit')
        break;
    elseif strcmp(data , 'echo')
        % loop until we receive response from server or until timeout
        tic
        % Attempting to read before t.BytesAvailable is non zero results in
        % in an exception
        while t.BytesAvailable == 0
            
            if toc > TIMEOUT
                fprintf('\n');
                fprintf('Did not receive any reply from the server in the designated time!\n');
                fprintf('Please check your connection or increase the timeout time!\n');
                return;
            end
            pause(.1);
        end
        % Read data from server
        data_rec = fread(t, t.BytesAvailable);
        fprintf('Server replied: %s\n', data_rec);
    end

end

% disconnect from server
fclose(t);
disp('Disconnected!')