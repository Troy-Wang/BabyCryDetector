function [ clippedVoice ] = clipping( voice, category )
%CLIPPING Three level clipping for pitch frequency estimation
%   input: voice data
%   input: category - '3level' or 'center'
%          '3level' means three level clipping 三电平削波
%          'center' means center clipping 中心削波
%   output: clipped voiced data

    L=length(voice);
    m = max(voice);
    n = min(voice);

    coeff = 0.68;
    threshold = coeff*m;
    
    a = voice;
    
    if category == '3level'
        for k=1:L ;                          %clipping
            if a(k)>=threshold
                %a(k)=a(k)-th0;
                a(k)=1;
            elseif a(k)<=(-threshold);
                %a(k)=a(k)+th0;
                a(k)=-1;
            else
                a(k)=0;
            end      
        end
    else
        for k=1:L ;                          %clipping
            if a(k)>=threshold
                a(k)=a(k)-threshold;
                %a(k)=1;
            elseif a(k)<=(-threshold);
                a(k)=a(k)+threshold;
                %a(k)=-1;
            else
                a(k)=0;
            end      
        end
    end
        
    clippedVoice = a;
    
end

