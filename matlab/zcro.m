function f=zcro(x)
%Calc the zero-crossing rate of the frames x
%   input: frames of voice data
%   output: zero-cross rate of each frame

f=zeros(size(x,1),1); 
for i=1:size(x,1)
   z=x(i,:);   
   for j=1:(length(z)-1);
      if z(j)*z(j+1)<0;
          f(i)=f(i)+1;
      end
   end
end