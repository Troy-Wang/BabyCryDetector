function [ smoothedPF ] = smoothing( PF )
%SMOOTHING Summary of this function goes here
%   input: raw pitch frequency
%   output: smoothed pitch frequency
%   This system uses PF1, 五点中值平滑和三点中值平滑组合

    disp('smoothing....');
    PF0=medfilt1(PF,5);  %五点中值平滑
    PF1=medfilt1(PF0,3); %三点中值平滑，PF1为五点中值平滑和三点中值平滑组合
    PF2=linsmooth(PF0,5);%五点线性平滑，PF2为五点中值平滑和五点线性平滑组合

%     w=[];
%     w=PF;
%     length(w)
%     length(PF2)
%     w1=w-PF2';
%     w1=medfilt1(w1,5);         %五点中值平滑
%     w1=linsmooth(w1,5);        %五点线性平滑
%     PF3=w1+PF2;       %二次平滑算法

%       figure(1)
%     subplot(411);
%     plot(PF);
%     xlabel('帧数')
%     ylabel('样点数')
%     title('原始基音周期轨迹')

%     subplot(412);
%     plot(PF1);
%     xlabel('帧数')
%     ylabel('样点数')
%     title('五点中值平滑和三点中值平滑组合')

%     subplot(413);
%     plot(PF2);
%     xlabel('帧数')
%     ylabel('样点数')
%     title('五点中值平滑和五点线性平滑组合')
% 
%     subplot(414);
%     plot(PF3);
%     xlabel('帧数')
%     ylabel('样点数')
%     title('二次平滑算法')
    
    smoothedPF = PF1;
    
end

