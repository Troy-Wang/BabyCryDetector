function [ smoothedPF ] = smoothing( PF )
%SMOOTHING Summary of this function goes here
%   input: raw pitch frequency
%   output: smoothed pitch frequency
%   This system uses PF1, �����ֵƽ����������ֵƽ�����

    disp('smoothing....');
    PF0=medfilt1(PF,5);  %�����ֵƽ��
    PF1=medfilt1(PF0,3); %������ֵƽ����PF1Ϊ�����ֵƽ����������ֵƽ�����
    PF2=linsmooth(PF0,5);%�������ƽ����PF2Ϊ�����ֵƽ�����������ƽ�����

%     w=[];
%     w=PF;
%     length(w)
%     length(PF2)
%     w1=w-PF2';
%     w1=medfilt1(w1,5);         %�����ֵƽ��
%     w1=linsmooth(w1,5);        %�������ƽ��
%     PF3=w1+PF2;       %����ƽ���㷨

%       figure(1)
%     subplot(411);
%     plot(PF);
%     xlabel('֡��')
%     ylabel('������')
%     title('ԭʼ�������ڹ켣')

%     subplot(412);
%     plot(PF1);
%     xlabel('֡��')
%     ylabel('������')
%     title('�����ֵƽ����������ֵƽ�����')

%     subplot(413);
%     plot(PF2);
%     xlabel('֡��')
%     ylabel('������')
%     title('�����ֵƽ�����������ƽ�����')
% 
%     subplot(414);
%     plot(PF3);
%     xlabel('֡��')
%     ylabel('������')
%     title('����ƽ���㷨')
    
    smoothedPF = PF1;
    
end

