function out=Task33()
    a = 3 * pi / 4
    T_10 = transl([3 - 3 * cos(a); 2; -3 * sin(a)]) * trotx(pi/2) * trotz(a);
    T_21 = transl([0.2; 0; 1])*trotx(-pi);

    figure;
    trplot(trotx(0), 'color', 'r', 'frame', '0','axis',[-2 6 -2 7 -2 6]);
    hold on;

    trplot(T_10*T_21, 'color', 'g',  'frame', '2','axis',[-2 6 -2 7 -2 6]);
    trplot(T_10, 'color', 'b',  'frame', '1','axis',[-2 6 -2 7 -2 6]);

    out = T_10*T_21
end