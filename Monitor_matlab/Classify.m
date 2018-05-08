function [ score ] = Classify(voice, fs, nBit)
%Classify Classifying Function for baby cry using 5 features extracted by corresponding functions.
%   input: voice data
%   input: sample rate
%   input: number of bits per sample
%   output: is this a baby cry? (0 for no, 1 for yes)
%   To do : construct a decision tree for classification

%     fid = fopen('result.txt','a');
    
    stdPitchFreq = 10;  %5 frames
    stdAvgFreq = 1000;
    stdSTE = 100;
    stdAcc = 200;
    stdZCR = 40;
    stdMFCC = 0;
    
    score = 0;
    
    
    feature_Freq = Freq(voice, fs, nBit);
    [feature_PitchFreq feature_PitchFreq2 ]= PitchFreq(voice , fs, nBit);
    [feature_STE feature_STEAcc ]=STE(voice, fs, nBit);
    feature_ZCR = ZCR(voice, fs, nBit);
    
    disp(feature_Freq);
    disp(feature_PitchFreq);
    disp(feature_PitchFreq2);
    disp(feature_STE);
    disp(feature_STEAcc);
    disp(feature_ZCR);
    
    if feature_Freq > stdAvgFreq
        score = score + 1;
        disp('freq yes');
    end
    
    if feature_PitchFreq > stdPitchFreq
        score = score + 1;
        disp('pitch freq yes');
    end
    
%     if feature_STE > stdSTE
%         score = score + 1;
%     end
    
    if feature_STEAcc > stdAcc
        score = score + 1;
    end
    
    if feature_ZCR > stdZCR
        score = score + 1;
        disp('zcr yes');
    end
    
    disp(score);
    
    if score >= 3
        disp('baby cry');
    end
    
    
%     fprintf(fid, '%f\t%f\t%f\t%f\t%f\t%f\n', feature_Freq,feature_PitchFreq, feature_PitchFreq2, feature_STE, feature_STEAcc, feature_ZCR);
%     
%     fclose(fid);
    
%     score = 

    
end

