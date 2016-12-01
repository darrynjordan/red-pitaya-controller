fn_end = getFracNum(100);
LEN = 2^15;
s1_inc = fn_end/LEN;
fn_start = getFracNum(1);
T = 100;
F = T*s1_inc - fn_start;
s2_inc = (fn_end - fn_start - F)/(LEN - T);

if (s1_inc == s2_inc)
    fprintf('Gradient criteria satisfied.\n');
else
    fprintf('WARNING: Gradient criteria NOT satisfied.\n');
end;

fprintf('\nT: \t%f\n', (LEN*(F + fn_start))/fn_end);
fprintf('F: \t%f\n', F);

fprintf('\nSynthesizer 1:\n');
fprintf('SRT: \t%f\n', 0);
fprintf('END: \t%f\n', fn_end);
fprintf('INC: \t%f\n', s1_inc);
fprintf('LEN: \t%f\n', LEN);
fprintf('BW: \t%f\n', getVco(fn_end));

fprintf('\nSynthesizer 2:\n');
fprintf('SRT: \t%f\n', fn_start);
fprintf('END: \t%f\n', fn_end - F);
fprintf('INC: \t%f\n', s2_inc);
fprintf('LEN: \t%f\n', LEN - T);
fprintf('BW: \t%f\n', getVco(fn_end) - getVco(fn_start));