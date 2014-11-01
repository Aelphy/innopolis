function out = Task31()
    T_10 = transl([4; 2; 0])*troty(pi)*trotz(-pi/2);
    T_21 = transl([-4; 4; 0])*troty(-pi/2)*trotx(pi)*trotx( pi/4);
    T_32 = transl([4; 5*sqrt(2); sqrt(2)])*trotx(3*pi/4)*trotz(pi/2);

    T = T_32 * T_21 * T_10;

    figure;
    trplot(trotx(0), 'color', 'r', 'frame', '0','axis',[-2 6 -2 7 -2 6]);
    hold on;

    trplot(T_10*T_21*T_32, 'color', 'm', 'frame', '3','axis',[-2 6 -2 7 -2 6]);
    trplot(T_10*T_21, 'color', 'b',  'frame', '2','axis',[-2 6 -2 7 -2 6]);
    trplot(T_10, 'color', 'g',  'frame', '1','axis',[-2 6 -2 7 -2 6]);

    out = T_10*T_21*T_32
end