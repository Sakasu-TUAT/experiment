clear all;,close all;
X=load('sample2d.txt');
[d,n]=size(X);

%% d次元の平均ベクトルを求める
m=zeros(d,1);
for ii = 1 : n
  m=m+X(:,ii);
end
m=m./n;

%% dxdの分散共分散行列を求める
%% まずは自己相関行列Rを求める
R=zeros(d,d);

%Rとmを使って分散共分散行列Sを求める
S=R-m*m';

%% Sの固有値と固有ベクトルを求める
[U D]=eig(S);
[value index]=max(diag(D));

%% 最大固有値に対応する固有ベクトルから直線の傾きaを求める
a=

%% 傾きがaである直線が点mを通ることを利用して切片bを求める
b=

% 直線ax+bを緑の直線で描画
x=[min(X(1,:)):.05:max(X(1,:))];
figure(1),clf,hold on,plot(X(1,:),X(2,:),'bo');
figure(1),plot(x,a.*x+b,'g-'); %直線ax+bを描画
axis square
