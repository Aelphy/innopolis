function out = Task32()
    a = 3 * pi / 4
    T_10 = transl([0; 0; 9]) * trotz(a);
    T_21 = transl([3; sqrt(18 - 18 * cos(a)); 0]) * trotz(-a) * troty(pi/2);

    figure;
    trplot(trotx(0), 'color', 'r', 'frame', '0','axis',[-2 6 -2 7 -2 6]);
    hold on;

    trplot(T_10*T_21, 'color', 'g',  'frame', '2','axis',[-2 6 -2 7 -2 6]);
    trplot(T_10, 'color', 'b',  'frame', '1','axis',[-2 6 -2 7 -2 6]);

    out = T_10*T_21
end