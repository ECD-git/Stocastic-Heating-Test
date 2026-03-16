# Stocastic-Heating-Test
A test simulation for the stocastic heating of particles in a randomly moving potential. For the Alpha-g masters project.

---

To distribute initial velocities by the Maxwell-Boltzman distribution, we use it's inverse CDF,

$$ \text{CDF}(v) = \text{erf}\bigg(\frac{x}{\sqrt{2}a}\bigg) - \sqrt{\frac{2}{\pi}}\frac{x}{a}\exp\bigg(-\frac{x^2}{2a^2}\bigg),$$

where $a = \sqrt{k_bT/M}$, and $\text{erf}$ is the error function, and all other symbols have their usual meanings.
We use the fact that the PDF of this distribution is well known and also the derivative of the CDF, and use Newton-Raphson method of numerican solving to get the a value of $v$ for random uniform distribution of CDF(v),

$$ x_{n+1} = x_n - \frac{f(x_n)}{f^{\'}(x_n)}.$$