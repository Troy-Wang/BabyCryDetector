function [ feature_STE feature_STEAcc ] = STE( voice, fs, nBit )
%STE Calc Short-Time Energy of the voice
%   input: voice data
%   input: sample rate
%   input: number of bits per sample
%   output: short-time-energy feature of the voice data

    disp('Feature STE');
    frameLength = 20*0.001*fs; %frame length
    frameInc = frameLength;   %frame inc = frame length
    voiceFrames = enframe(voice, frameLength, frameInc);
    [framesNum frameLen] = size(voiceFrames); 
    
    temp = voiceFrames.^2;
    energy = sum(temp,2);
    
    feature_STE = mean(energy(energy>=(0.2*max(energy))));
    
    acc = diff(energy);
    feature_STEAcc = max(acc);
%     sortedAcc = sort(acc,'descend');
%     cutting = floor(length(sortedAcc)/2);
%     feature_STEAcc = mean(sortedAcc(1:cutting));
%     feature_STEAcc = mean(acc(acc>=(0.5*max(acc))));
    
%     plot(energy);
%     xlabel('Frame Num');
%     ylabel('Energy');
%     legend('Short-time Energy');

end

