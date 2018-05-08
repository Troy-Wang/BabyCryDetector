function [ feature_PitchFreq feature_PitchFreq2 ] = PitchFreq( voice, fs, nBit )
%PITCHFREQ Calc the pitch frequency feature of the voice
%   input: voice data
%   input: sample rate
%   input: number of bits per sample
%   output: pitch frequency feature of the voice data

    disp('Feature PitchFreq');
    voice = FIR(voice, fs, nBit, 3000);     %low pass filter (3000Hz)
    voice = clipping(voice, '3level');      %clipping (three level clipping ����ƽ����)
    
    frameLength = 0.03*fs;  %���ݲ���Ƶ��ѡ��֡��
    frameInc = frameLength/3;   %֡��Ϊ֡��1/3
    voiceFrames = enframe(voice, frameLength, frameInc);
    [framesNum frameLen] = size(voiceFrames); 
%     size(voiceFrames)
%     disp(framesNum);


    cutting = floor(0.003*fs);
    for m=1:framesNum;           %��ÿһ֡���ʱ����غ���
        Rm0=sum(voiceFrames(m,:).^2);   %STE of the frame
        for k=1:frameLength;
            Rm(k)=0;
            for i=(k+1):frameLength;
                Rm(k)=Rm(k)+voiceFrames(m,i)*voiceFrames(m,i-k);
            end
        end
        p=Rm(cutting:frameLength);                %��ֹ���У�ȥ��ǰ��3ms*fs����ֵ�ϴ�ĵ�  
%         if sum(p~=0)~=0
%             figure(m);
%             plot(p);
%         end
        [Rmax,N(m)]=max(p);        %��ȡ��һ������غ���������
        if Rmax<0.25*Rm0 || Rmax==0          %������ֵС��STE��25%����STEΪ0������Ϊ�������ģ������������źţ�������������0
            N(m)=0;
        else
            N(m)=N(m)+cutting;
            N(m)=fs./N(m);
        end
    end 
%      N=N+cutting;
    T=N;
%      figure(1);stem(T,'.');axis([0 length(T) 0 max(T)]);
%      xlabel('֡��(n)');ylabel('����(ms)');title('��֡��������');
    
    pitchFreq = smoothing(T);
%       figure(2);
     plot(pitchFreq);
    
    feature_PitchFreq = sum(pitchFreq>200);     %we're interested in frames whose pitch frequecy is bigger than 200
    feature_PitchFreq2 = sum(pitchFreq>200)/sum(pitchFreq~=0);
    
end

