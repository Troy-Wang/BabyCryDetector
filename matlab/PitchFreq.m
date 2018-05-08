function [ feature_PitchFreq feature_PitchFreq2 ] = PitchFreq( voice, fs, nBit )
%PITCHFREQ Calc the pitch frequency feature of the voice
%   input: voice data
%   input: sample rate
%   input: number of bits per sample
%   output: pitch frequency feature of the voice data

    disp('Feature PitchFreq');
    voice = FIR(voice, fs, nBit, 3000);     %low pass filter (3000Hz)
    voice = clipping(voice, '3level');      %clipping (three level clipping 三电平削波)
    
    frameLength = 0.03*fs;  %根据采样频率选择帧长
    frameInc = frameLength/3;   %帧移为帧长1/3
    voiceFrames = enframe(voice, frameLength, frameInc);
    [framesNum frameLen] = size(voiceFrames); 
%     size(voiceFrames)
%     disp(framesNum);


    cutting = floor(0.003*fs);
    for m=1:framesNum;           %对每一帧求短时自相关函数
        Rm0=sum(voiceFrames(m,:).^2);   %STE of the frame
        for k=1:frameLength;
            Rm(k)=0;
            for i=(k+1):frameLength;
                Rm(k)=Rm(k)+voiceFrames(m,i)*voiceFrames(m,i-k);
            end
        end
        p=Rm(cutting:frameLength);                %防止误判，去掉前边3ms*fs个数值较大的点  
%         if sum(p~=0)~=0
%             figure(m);
%             plot(p);
%         end
        [Rmax,N(m)]=max(p);        %读取第一个自相关函数的最大点
        if Rmax<0.25*Rm0 || Rmax==0          %如果最大值小于STE的25%或者STE为0，则认为是无声的（或者是清音信号），基音周期置0
            N(m)=0;
        else
            N(m)=N(m)+cutting;
            N(m)=fs./N(m);
        end
    end 
%      N=N+cutting;
    T=N;
%      figure(1);stem(T,'.');axis([0 length(T) 0 max(T)]);
%      xlabel('帧数(n)');ylabel('周期(ms)');title('各帧基音周期');
    
    pitchFreq = smoothing(T);
%       figure(2);
     plot(pitchFreq);
    
    feature_PitchFreq = sum(pitchFreq>200);     %we're interested in frames whose pitch frequecy is bigger than 200
    feature_PitchFreq2 = sum(pitchFreq>200)/sum(pitchFreq~=0);
    
end

