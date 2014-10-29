function out = Task33()
    a = 3*pi/4

    T10 = transl([3 - 3*cos(a); 2; -3*sin(a)])*trotx(pi/2)*trotz(a)
    T21 = transl([0.2; 0; 1])*trotx(pi/2)

    trplot(trotx(0), 'color', 'g', 'frame', 1,'axis',[-10, 10, -10, 10, -10, 10])
    hold on
    trplot(T10) 
    hold on
    tranimate(T10*T21)

    out = T10*T21
end
