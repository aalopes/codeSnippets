%% TCP/IP server
% 
% Alexandre Lopes (adapted from MathWorks docs)
% 22.07.2015

PORT = 56000;

t = tcpip('localhost', PORT, 'NetworkRole', 'server');

% Open a connection. This will not return until a connection is received.

fopen(t);


while 1
    % Read data 

    % The pause is needed because Matlab's socket implementation seems to be kind 
    % of broken. The server doesn't seem to wait for the client.
    % cf. http://stackoverflow.com/questions/20271970/matlab-sockets-wait-for-response

    while t.BytesAvailable == 0
        pause(.1)
    end
    data = fread(t, t.BytesAvailable);
    fprintf('%s \n',data);

    if strcmp(data, 'quit')
        break
    elseif strcmp(data, 'echo')
        fwrite(t,data);
    end
end
fclose(t);
