function out=rot_rcub()
    hold off
    
    for i=1:200
        m = trotx(i/50) * troty(-i/10) * trotz(i/30);
        h = rcube(m);
        pause(0.005);
        delete(h);
    end
    rcube(m);
end