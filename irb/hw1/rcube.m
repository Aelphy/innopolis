function out = rcube(rot)
    A = (rot*[-0.5 -0.5 -0.5 1].').';
    B = (rot*[0.5 -0.5 -0.5 1].').';
    C = (rot*[-0.5 0.5 -0.5 1].').';
    D = (rot*[-0.5 -0.5 0.5 1].').';
    E = (rot*[-0.5 0.5 0.5 1].').';
    F = (rot*[0.5 -0.5 0.5 1].').';
    G = (rot*[0.5 0.5 -0.5 1].').';
    H = (rot*[0.5 0.5 0.5 1].').';
    P = [A;B;F;H;G;C;A;D;E;H;F;D;E;C;G;B];

    out = plot3(P(:,1),P(:,2),P(:,3));

    hold on;
    trplot(trotx(0), 'color', 'r', 'frame', '','axis',[-2 6 -2 7 -2 6]);
end
