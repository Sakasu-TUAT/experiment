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
disp(index);
disp(value);
best = disp(value(1));
secondBest = disp(value(2));

u=[U(:, index(1)), U(:, index(2))];
disp(u);
Z=zeros(2, n);
for ii = 1 : n
  Z(:, ii) = u'*(X(:, ii)-m);
end

lamda=zeros(4,n)
for ii = 1 : n
  Z(:, ii) = u'*(X(:, ii)-m);
end

S = sum(value)

valueSum = 0;
for ii = 1 : d
  valueSum = valueSum + value(ii);
  if ii == 1  
    figure(2),clf,hold on,plot(ii, valueSum/S, 'bo');
  elseif ii >= 2
    figure(2),plot(ii, valueSum/S, 'bo');
  end
end



disp(Z);

figure(1),clf,hold on,plot(Z(1, 1:50),Z(2,1:50),'bo');
figure(1),plot(Z(1, 51:100),Z(2, 51:100),'ro');
figure(1),plot(Z(1, 101:150),Z(2, 101:150),'go');
axis square
