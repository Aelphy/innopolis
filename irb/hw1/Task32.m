function out = Task32()
    a = 3*pi/4

    T10 = transl([0; 0; -9])*trotz(-a)
    T21 = transl([0; 0; -3])*trotx(-a)*troty(-pi/2)

    trplot(trotx(0), 'color', 'g', 'frame', 'A','axis',[-15, 15, -15, 15, -15, 15])
    hold on
    trplot(T10) 
    hold on
    tranimate(T10*T21)

    out = T10*T21
end
