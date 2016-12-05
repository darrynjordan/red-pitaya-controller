T = 0;
F = 0;
LEN = 32768;

s1_fn_start = 0;
s1_fn_end = getFracNum(100);

s2_fn_start = getFracNum(1);

INC = s1_fn_end/LEN;

% F > 0 ensures there will be at least two crossings 
while (F <= 0)
    T = T + 1;
    s2_fn_end = INC*(LEN - T) + s2_fn_start;
    F = s1_fn_end - s2_fn_end;
end;

s2_fn_end = INC*(LEN - T) + s2_fn_start;
F = s1_fn_end - s2_fn_end;

fprintf('\nT: \t%f\n', T);
fprintf('F: \t%f\n', F);
fprintf('INC: \t%f\n', INC);

fprintf('\nSynthesizer 1:\n');
fprintf('SRT: \t%f\n', 0);
fprintf('END: \t%f\n', s1_fn_end);
fprintf('LEN: \t%f\n', LEN);
fprintf('BW: \t%f\n', getVco(s1_fn_end));

fprintf('\nSynthesizer 2:\n');
fprintf('SRT: \t%f\n', s2_fn_start);
fprintf('END: \t%f\n', s2_fn_end);
fprintf('LEN: \t%f\n', LEN - T);
fprintf('BW: \t%f\n', getVco(s2_fn_end) - getVco(s2_fn_start));