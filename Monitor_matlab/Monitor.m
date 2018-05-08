function Monitor
%Monitor Main monitor for the baby cry detector

    record = [];        %save the 15s' record after volumn becomes bigger than threshold
    fs = 8000;          %recording frequency
    nBit = 16;          %recording bits per sample (dataType = 'double')
    
    %Parameters Setting
    secondsToRecord = 3;
    soundThreshold = 0.6;   % volumn threshold (0.0 ~ 1.0)
 
    %Recording Setting
    ai = analoginput('winsound');
    addchannel(ai,[1 2]);
%    set(ai, 'LogToDiskMode', 'overwrite');
%    set(ai, 'LogFileName', 'c:\voice.txt')
    set(ai,'SampleRate',8000);
    set(ai, 'TriggerType', 'manual');
    set(ai, 'TriggerRepeat', Inf);
    samplesToRecord = ceil(ai.SampleRate * secondsToRecord);
    set(ai, 'SamplesPerTrigger', samplesToRecord );
    set(ai,'StartFcn',@soundStartFcn);
    set(ai, 'TimerPeriod', 0.1);
    set(ai, 'TimerFcn', @soundTimerFcn);

    %Create a figure to show the real-time voice volumn
    fig = figure('DoubleBuffer','on', ...
                'Name', 'Enviroment Volumn Detector', ...
                'NumberTitle', 'off', ...
                'WindowStyle', 'docked', ...
                'Toolbar', 'none', ...
                'MenuBar', 'none', ...
                'Color',[.5 .5 .5], ...
                'CloseRequestFcn', @figureCloseFcn, ...%clean up when done
                'DeleteFcn', @figureDeleteFcn);

    timePrevious = [];
    start(ai);
    
    
    %Start
    function soundStartFcn(vid, event)
        timePrevious = now;
    end


    %Executes every 0.1(set by TimePeriod)
    function soundTimerFcn(vid, event)
        try
            timeCurrent = now;
        catch
            return;
        end
        
        samplesRequested = ceil((timeCurrent - timePrevious) * (60*60*24) *ai.SampleRate);
        %disp(samplesRequested);
        warning('off','daq:peekdata:requestedSamplesNotAvailable');

        try
            sound = peekdata(ai, samplesRequested);
        catch
            sound = zeros(samplesRequested, length(ai.Channel));
        end

        warning('on','daq:peekdata:requestedSamplesNotAvailable');
        sound = sound - mean(sound(:,1));% Center about the mean.
        soundMax = max(max(abs(sound)));% Calculate max deviation from mean.
        
        timePrevious = timeCurrent;
        
        % Make our figure current.
        figOld = get(0,'CurrentFigure');
        if fig ~= figOld
            set(0, 'CurrentFigure', fig);
        end
        plot(sound);
        % axis([0 size(sound,1) -1 1]);
        ylim([-1 1]);
        set(gca,'XTick',[]);s

        % Noise volumn arrives threshold?
        if soundMax > soundThreshold
            noise = true;
        else
            noise = false;
        end

        if ~islogging(ai)
            if noise
                set(gcf, 'Color', [1 0 0]);
                % trigger(ai);
                % noise handler
                volumnOverThreshold(soundMax);
            else
                %if noise didn't arrive the threshold
                set(gcf, 'Color', [.5 .5 .5]);
            end;
        end
        
        if fig ~= figOld
            set(0, 'CurrentFigure', figOld);
        end
        
    end


    % What to do when noise arrives threshold
    function volumnOverThreshold(soundMax)
%         disp(soundMax);
        startRecording();
        Analyze(record, fs, nBit);
        pause(5);
    end

    %Clean up
    function figureCloseFcn(obj, event)
        try
           stop(ai);
        catch
        end
        closereq;
    end

    function figureDeleteFcn(obj, event)
        delete(ai);
    end

    function startRecording()
        
        clear all;
        disp('Volumn over threshold! Start recording!');
        duration = 15;
        record = wavrecord(fs*duration,fs,1);
        disp('recording finished');
        
%         stop(ai);
%         delete(ai);
%         ai = analoginput('winsound');
%         addchannel(ai,1); 
%         set(ai,'SampleRate',44100);
% %         ai.SampleRate=44100; 
%         disp(ai.SampleRate);
%         duration = 15;
%         ActualRate = get(ai,'SampleRate'); 
%         set(ai,'SamplesPerTrigger',duration*ActualRate)
%         start(ai);
%         i = 1;
%         disp('Recording......');
%         while ai.SamplesAcquired < ai.SamplesPerTrigger 
%             if strcmp(ai.Running, 'On')
%                 while ai.SamplesAcquired < 1000*i
%                 end
%                 i = i + 1;
%             else
%                 break;
%             end
%         end
%         [data t] = getdata(ai,ai.SamplesAcquired);
%         name='mywav.wav';
%         wavwrite(data,name); 
%         stop(ai);
%         delete(ai);
        
    end

end

