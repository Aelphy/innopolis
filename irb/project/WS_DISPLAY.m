function WS_DISPLAY
    % initialization
    L = [1,1,0.5]
    Q = [0,0,-pi/2,0,0,0]

    L1 = Link([Q(1) 0 0 0],'standard')
    L2 = Link([Q(2)-pi/2 0 0 pi/2],'standard')
    L3 = Link([Q(3)+pi 0 0 -pi/2],'standard')
    L4 = Link([Q(4) 0 L(1) 0],'standard')
    L5 = Link([Q(5)+pi/2 0 L(2) 0],'standard')
    L6 = Link([Q(6) 0 0 -pi/2],'standard')
    L7 = Link([0 0 L(3) 0],'standard')

    robot = SerialLink([L1 L2 L3 L4 L5 L6 L7], 'name', 'robot'); 
    
    X = []
    Y = []
    Z = []
    
    [q1,q2,q3] = ndgrid(0:pi/10:2*pi);
    q1 = q1(:);
    q2 = q2(:);
    q3 = q3(:);
                
    [trans_m] = robot.fkine([q1,q2,q3,zeros(length(q1), 1),zeros(length(q1), 1),zeros(length(q1), 1),zeros(length(q1), 1)]);
    
    X = trans_m(1, 4, :);
    Y = trans_m(2, 4, :);
    Z = trans_m(3, 4, :);
    
    X = X(:);
    Y = Y(:);
    Z = Z(:);

    % plot the pint cloud
    % scatter3(X,Y,Z);
    
    dt = DelaunayTri(X,Y,Z); 
    [tri Xb]= freeBoundary(dt);
    
    trisurf(tri,Xb(:,1),Xb(:,2),Xb(:,3), 'FaceColor', 'cyan', 'faceAlpha', 0.8);
end