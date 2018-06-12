clear; close all

load('data.mat')

n2 = sizes.^2;
n2n = (3*(sizes.^2) + sizes) / 4;
nm1 = sizes - 1;

%% basic operations

figure
hold on
plot(sizes, brute_ops, '-o')
plot(sizes, n2)
plot(sizes, n2n)
title('Brute force average basic operations')
xlabel('Set size')
ylabel('Avg. basic operations')
xlim([sizes(1) sizes(end)])
lgd = legend('brute\_force\_median', 'n^2 (reference)', '(3n^2+n)/4 (reference)');
lgd.Location = 'northwest';

figure
hold on
plot(sizes, med_ops, '-o')
plot(sizes, sizes)
plot(sizes, 2*nm1)
plot(sizes, 3*nm1)
plot(sizes, 4*nm1)
title('Median average basic operations')
xlabel('Set size')
ylabel('Avg. basic operations')
xlim([sizes(1) sizes(end)])
lgd = legend('median', 'n (reference)', '2(n-1) (reference)', '3(n-1) (reference)', '4(n-1) (reference)');
lgd.Location = 'northwest';

figure
hold on
plot(sizes, brute_ops, '-o')
plot(sizes, med_ops, '-*')
title('Median vs. brute force average basic operations')
xlabel('Set size')
ylabel('Avg. basic operations')
xlim([sizes(1) sizes(end)])
lgd = legend('brute\_force\_median', 'median');
lgd.Location = 'northwest';

%% execution time

scale = brute_time ./ brute_ops;
figure
hold on
plot(sizes, brute_time, '-o')
plot(sizes, scale.*n2)
plot(sizes, scale.*n2n)
title('Brute force average execution time')
xlabel('Set size')
ylabel('Avg. execution time (per 100 repetitions)')
xlim([sizes(1) sizes(end)])
lgd = legend('brute\_force\_median', 'n^2 (scaled reference)', '(3n^2+n)/4 (scaled reference)');
lgd.Location = 'northwest';

scale = med_time ./ med_ops;
figure
hold on
plot(sizes, med_time, '-o')
plot(sizes, scale.*sizes)
plot(sizes, 2*scale.*nm1)
plot(sizes, 3*scale.*nm1)
plot(sizes, 4*scale.*nm1)
title('Median average execution time')
xlabel('Set size')
ylabel('Avg. execution time (per 100 repetitions)')
xlim([sizes(1) sizes(end)])
lgd = legend('median', 'n (scaled reference)', '2(n-1) (scaled reference)', '3(n-1) (scaled reference)', '4(n-1) (scaled reference)');
lgd.Location = 'northwest';

figure
hold on
plot(sizes, brute_time, '-o')
plot(sizes, med_time, '-*')
title('Median vs. brute force average execution time')
xlabel('Set size')
ylabel('Avg. execution time (per 100 repetitions)')
xlim([sizes(1) sizes(end)])
lgd = legend('brute\_force\_median', 'median');
lgd.Location = 'northwest';
