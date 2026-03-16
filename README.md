# Stocastic-Heating-Test
A test simulation for the stocastic heating of particles in a randomly moving potential. For the Alpha-g masters project.

---

To distribute initial velocities by the Maxwell-Boltzman distribution, we use the inverse CDF,

$$ C_v(v) = {\rm erf}\left(\frac{v}{\sqrt{2k_B T/m}}\right) - \sqrt{\frac{2}{\pi}} \frac{ v \; \exp(-mv^2/2k_B T) }{\sqrt{k_B T / m}} $$