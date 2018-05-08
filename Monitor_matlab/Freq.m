function [ feature_avgFreq ] = Freq( voice, fs, nBit )
%FREQ Calc frequency feature of the voice
%   input: voice data
%   input: sample rate
%   input: number of bits per sample
%   output: frequency feature of the voice

    disp('Feature Freq');
    xfft = fft(voice);
    df = fs/length(xfft);
    Fx = df*(0:length(xfft)-1);
    xFFT = abs(xfft);
    xFFT(1) = 0;

    Fx = Fx(Fx<6000);
    xFFT = xFFT(1:length(Fx));
    xFFT = smoothing(xFFT);

    maxFFT = max(xFFT);
    % meanFreq = mean(Fx(find(xFFT>=(maxFFT*0.25))));

    xFFT1 = xFFT(find(xFFT>=(maxFFT*0.25)));
    Fx1 =Fx(find(xFFT>=(maxFFT*0.25)));

%     length(xFFT1)
%     length(Fx1)

    feature_avgFreq = sum(Fx1*xFFT1)/sum(xFFT1);

    figure(2);
    plot(Fx,xFFT);
    ylabel('Magnitude (dB)');
    xlabel('Frequency (Hz)');

end

