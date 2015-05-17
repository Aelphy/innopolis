function [Ke, Kx, G] = preview_control_params(T, Zh, N)
    R = 1e-6;
    Qe = 1;
    Qdpos = 0;
    Qdvel = 0;
    Qdaccel = 0;
    g = 9.8;
    
    A = [1 T T^2/2;0 1  T;0 0 1];
    B = [T^3/6;T^2/2;T];
    C = [1 0 -Zh/g];
    
    AA = vertcat(horzcat([1], C*A),horzcat(zeros(3,1), A));
    BB = vertcat([C*B], [B]);
    RR = R;
    QQ = diag([Qe, Qdpos, Qdvel, Qdaccel]);
    
    PP = dare(AA,BB,QQ,RR);
    SS = 1.0/(RR + BB'*PP*BB);
    KK = SS*BB'*PP*AA;
    
    Ke = KK(1,1);
    Kx = KK(1,2:4);
    
    Ac = AA - BB*KK;
    XX = -Ac' * PP * [1,0,0,0]';
    
    G = [-Ke];

    for i=2:1:N
      G = [G SS * BB' * XX];
      XX = Ac' * XX;
    end
end