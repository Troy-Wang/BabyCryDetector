function [ output ] = Analyze(voice, fs, nBit)
%Use feature extraction to determine if it is baby's cry
%   call Classify to tell if the voice is a baby cry
    disp('Analyzing......');
% 
%     [voice fs nBit]=wavread('mywav.wav');
%     voice = voice(:,1);
%     wavplay(voice,fs);
%     voice = voice(:,1);
    Classify(voice, fs, nBit);
        
end

