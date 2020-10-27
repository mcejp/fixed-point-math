import math

F = 12
L = 32

DROP = 3 * F + 2 - L
DROP1 = DROP // 2
DROP2 = DROP - DROP1

print(f"drop {DROP} / {DROP1}+{DROP2}")

for Thres in range(32):
    X_ge = 2**(Thres)
    x_ge = 2**(Thres - F)

    X_le = 2 ** (Thres + 1) - 1
    x_le = 2 ** (Thres + 1 - F) - 2 ** -F

    y_ge = 1 / math.sqrt(x_le)
    Y_ge = int(math.floor(2**F * y_ge))
    assert Y_ge == int(math.floor(2**(3 * F / 2) / math.sqrt(X_le)))

    y_le = 1 / math.sqrt(x_ge)
    Y_le = int(math.ceil(2**F * y_le))

    X_error_le = 2**DROP - 1
    X_error_rel_le = X_error_le / X_ge

    Y2_error_le = (2**DROP1 - 1) * Y_le + (2**DROP2 - 1) * Y_le + (2**DROP1 - 1) * (2**DROP2 - 1)
    Y2_error_rel_le = Y2_error_le / (Y_ge * Y_ge)

    max_error_rel = max(X_error_rel_le, Y2_error_rel_le)

    print(f"{Thres=:2d} X<={X_le:10d} x<={x_le:13.5f} y>={y_ge:7.4f} Y>={Y_ge:10d} "
          f"err_X<={X_error_rel_le * 100:7.2f}% err_Y<={Y2_error_rel_le * 100:7.2f}% err<={max_error_rel * 100:7.2f}% "
          )
