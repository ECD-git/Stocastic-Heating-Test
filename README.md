# Stocastic-Heating-Test
A test simulation for the stocastic heating of particles in a randomly moving potential. For the Alpha-g masters project.

---

To distribute initial velocities by the Maxwell-Boltzman distribution, we use it's inverse CDF,

$$ \text{CDF}(v) = \text{erf}\bigg(\frac{x}{\sqrt(2)a}\bigg) - \sqrt{\frac{2}{\pi}}\frac{x}{a}\exp\bigg(-\frac{x^2}{2a^2}\bigg)$$

