g = 9.8;
Zc = 1;
T = 1e-4;
N = 5050;
sim_time = 10;

[Ke, Kx, G] = preview_control_params(T, Zc, N);

D_o = [1 3 5]';                % delays
D_e = [2 4 6]';                % delays
t = 0 : T : sim_time + N * T;  % signal evaluation time
width = 1;                         % width of each pulse

desired_zmp = 0.1 * pulstran(t, D_o, 'rectpuls', width) - 0.1 * pulstran(t, D_e, 'rectpuls', width);
desired_zmp = [t' desired_zmp'];