order = 12;
I = e.^(pi./(2.^(1:2:order)));
Q = e.^(pi./(2.^(2:2:order)));
I = [I -I];
Q = [Q -Q];
W = logspace(-4, -.7, 512);
[B A] = zp2tf(I, 1./I, 1);
h1 = freqz(B,A,W);
h1gain = 1/abs(h1(end));
[B A] = zp2tf(I, 1./I, h1gain);
h1 = freqz(B,A,W);
[B A] = zp2tf(Q, 1./Q, 1);
h2 = freqz(B,A,W);
h2gain = 1/abs(h2(end));
[B A] = zp2tf(Q, 1./Q, h2gain);
h2 = freqz(B,A,W);
figure(1);
semilogx(W, 180/pi.*[unwrap(angle(h1))- unwrap(angle(h2))]);
figure(2);
semilogx(W, abs([h1;h2]));