% ensure that ramp gradients are equal
fn_start = getFracNum(1);
fn_end = fn_start*100;
length = (fn_end/fn_start)*325;

t_diff = (fn_start*length)/fn_end;

if (mod(t_diff, 1) == 0)
    fprintf('Gradient criteria satisfied.\n');
end;

% observe effects of choices
s1_inc = fn_end/length;
s2_inc = (fn_end - fn_start)/length;

fprintf('Synth 1 Inc: %f\n', s1_inc);
fprintf('Synth 2 Inc: %f\n', s2_inc);
