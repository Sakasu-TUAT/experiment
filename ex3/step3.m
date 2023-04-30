clear all;,close all;
X=load('iris4d.txt');
[d,n]=size(X);

%disp([d, n]);

disp(X)

%% d次元の平均ベクトルを求める
m=zeros(d,1);
for ii = 1 : n
  m=m+X(:,ii);
end
m=m./n;

%% dxdの分散共分散行列を求める
%% まずは自己相関行列Rを求める
R=zeros(d,d);
for ii = 1 : n
    R = R + X(:, ii)*X(:, ii)';
end
R=R./n;

%Rとmを使って分散共分散行列Sを求める
S=R-m*m';

% Sの固有値と固有ベクトルを求める
%D...Sの固有値が対角要素に格納された行列
%U...各固有値に対応する固有ベクトルが縦に格納された行列
[U D]=eig(S); 

%valueはD(固有値)の対角要素
[value index]=sort(diag(D), 'descend');

x_list=cell(1,d);
disp(size(x_list));

error_list=cell(1,d);

for r = 1 : d
  for jj = 1 : n
    x_i = X(:, r);
    disp(size(x_i));
    x_hat=m+U*U'*(x_i-m)
    x_list{r}=x_hat;
    disp(x_hat);
    temp = temp + (x_i-x_hat)'*(x_i-x_hat);
    error_list{r} = (1./n)*(x_i-x_hat)'*(x_i-x_hat)

end
disp(x_list);

axis square
