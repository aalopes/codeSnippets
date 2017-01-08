%% Canny edge detection using the GPU (CUDA), with code benchmarking
%  Unfortunately this doesn't work at the moment since Canny is currently
%  not supported on the GPU!
%
% 2016 Alexandre Lopes

addpath('../images/')
tic;

% read image
init_t = tic;
I = gpuArray(imread('pic32mz2048ech100_07_se_1500x_5kv_15mm_no_border.png'));
io_t = toc; % io

% convert to grayscale
gray = rgb2gray(I);
conv_t = toc; % conversion to grayscale

I_edges = edge(gray, 'canny');
canny_t = toc; % Canny edge detection

% plot both superimposed
imshowpair(gray, I_edges)

fprintf('Elapsed wall time (IO)    %d\n', (io_t - init_t));
fprintf('Elapsed wall time (Conv)  %d\n', (conv_t - io_t));
fprintf('Elapsed wall time (Canny) %d\n', (canny_t  - conv_t));
