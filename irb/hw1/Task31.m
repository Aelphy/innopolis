function out = Task31()
    T10 = transl([4; 2; 0])*troty(pi)*trotz(-pi/2)
    T21 = transl([-4; 4; 0])*troty(-pi/2)*trotx(5*pi/4)
    T23 = transl([4; 5*sqrt(2); sqrt(2)])*trotx(3*pi/4)*trotz(pi/2)
    
    trplot(trotx(0), 'color', 'g', 'frame', '1','axis',[-10, 10, -10, 10, -10, 10])
    hold on
    trplot(T10) 
    hold on
    trplot(T10*T21)
    hold on
    tranimate(T10*T21*T23)

    out = T10*T21*T23
end
