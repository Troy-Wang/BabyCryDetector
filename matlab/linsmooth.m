function [y] = linsmooth(x,n,wintype)
% linsmooth linear smoothing
% input: x: ����
% input: n: ���� 
% input: wintype: �����ͣ�ȱʡΪ 'hann'
% output: linear-smoothed data

if nargin<3
   wintype='hann';
end
if nargin<2
   n=3;
end
win=hann(n);
win=win/sum(win); % ��һ��
[r,c]=size(x);
if min(r,c)~=1
   error('sorry, no matrix here!:(')
end

if r==1 % ������
    len=c;
else
   len=r;
   x=x.';
end
y=zeros(len,1);
if mod(n,2)==0
   l=n/2;
   x = [ones(1,l)*x(1) x ones(1,l)*x(len)]';
else
   l=(n-1)/2;
   x = [ones(1,l)*x(1) x ones(1,l+1)*x(len)]';
end

for k=1:len
	y(k) = win'*x(k:k+n-1);
end