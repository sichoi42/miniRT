#include "mlx.h"

int	main(void)
{
	void	*m_ptr;
	void	*w_ptr;

	m_ptr = mlx_init();
	w_ptr = mlx_new_window(m_ptr, 1200, 800, "test");
	mlx_loop(m_ptr);
	return (0);
}