close all; clear all;
load('data.mat');
l2_x = 2.^(0:0.1:30);
l2_y = log2(l2_x);
l2_y2 = log2(l2_x + 1);

% basic operations 2^x
figure
hold on
plot(l2_x, l2_y)
plot(l2_x, l2_y - 1)
plot(l2_x, l2_y2)
plot(sets2, basic_ops2(:, 1), '-o')
plot(sets2, basic_ops2(:, 2), '-*')
set(gca, 'XScale', 'log')
title('Average-Case Basic Operations for Sets of 2^x')
xlabel('Set size')
ylabel('Avg. basic operations')
lgd = legend('log2(x)', 'log2(x) - 1', 'log2(x + 1)', 'value present', 'value not present');
lgd.Location = 'northwest';

% basic operations 3^x
figure
hold on
plot(l2_x, l2_y)
plot(l2_x, l2_y - 1)
plot(l2_x, l2_y2)
plot(sets3, basic_ops3(:, 1), '-o')
plot(sets3, basic_ops3(:, 2), '-*')
set(gca, 'XScale', 'log')
title('Average-Case Basic Operations for Sets of 3^x')
xlabel('Set size')
ylabel('Avg. basic operations')
lgd = legend('log2(x)', 'log2(x) - 1', 'log2(x + 1)', 'value present', 'value not present');
lgd.Location = 'northwest';

% basic operations 10^x
figure
hold on
plot(l2_x, l2_y)
plot(l2_x, l2_y - 1)
plot(l2_x, l2_y2)
plot(sets10, basic_ops10(:, 1), '-o')
plot(sets10, basic_ops10(:, 2), '-*')
set(gca,'XScale','log')
title('Average-Case Basic Operations for Sets of 10^x')
xlabel('Set size')
ylabel('Avg. basic operations')
lgd = legend('log2(x)', 'log2(x) - 1', 'log2(x + 1)', 'value present', 'value not present');
lgd.Location = 'northwest';

% execution time 2^x
figure
hold on
ex_scale = mean(mean(diff(ex_time2)));
plot(l2_x, l2_y * ex_scale)
plot(l2_x, (l2_y - 1) * ex_scale)
plot(l2_x, l2_y2 * ex_scale)
plot(sets2, ex_time2(:, 1), '-o')
plot(sets2, ex_time2(:, 2), '-*')
set(gca, 'XScale', 'log')
title('Average-Case Execution Time for Sets of 2^x')
xlabel('Set size')
ylabel('Avg. execution time per 10^6 repetitions')
lgd = legend('log2(x) scaled', 'log2(x) - 1 scaled', 'log2(x + 1) scaled', 'value present', 'value not present');
lgd.Location = 'northwest';

% execution time 3^x
figure
hold on
plot(l2_x, l2_y * ex_scale)
plot(l2_x, (l2_y - 1) * ex_scale)
plot(l2_x, l2_y2 * ex_scale)
plot(sets3, ex_time3(:, 1), '-o')
plot(sets3, ex_time3(:, 2), '-*')
set(gca, 'XScale', 'log')
title('Average-Case Execution Time for Sets of 3^x')
xlabel('Set size')
ylabel('Avg. execution time per 10^6 repetitions')
lgd = legend('log2(x) scaled', 'log2(x) - 1 scaled', 'log2(x + 1) scaled', 'value present', 'value not present');
lgd.Location = 'northwest';

% execution time 10^x
figure
hold on
plot(l2_x, l2_y * ex_scale)
plot(l2_x, (l2_y - 1) * ex_scale)
plot(l2_x, l2_y2 * ex_scale)
plot(sets10, ex_time10(:, 1), '-o')
plot(sets10, ex_time10(:, 2), '-*')
set(gca, 'XScale', 'log')
title('Average-Case Execution Time for Sets of 10^x')
xlabel('Set size')
ylabel('Avg. execution time per 10^6 repetitions')
lgd = legend('log2(x) scaled', 'log2(x) - 1 scaled', 'log2(x + 1) scaled', 'value present', 'value not present');
lgd.Location = 'northwest';
