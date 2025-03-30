#include "../../lib/philo.h"

void	change_death(t_data *data)
{
	pthread_mutex_lock(&data->lock_death);
	data->dead = 1;
	pthread_mutex_unlock(&data->lock_death);
}

int	check_finished(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->lock_finished);
	res = data->finished;
	pthread_mutex_unlock(&data->lock_finished);
	return (res);
}

int	check_death(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->lock_death);
	if (data->dead == 0)
		res = 0;
	else
		res = 1;
	pthread_mutex_unlock(&data->lock_death);
	return (res);
}

int	case_one(t_data *data)
{
	data->start_time = get_time();
	pthread_mutex_lock(&data->lock);
	if (pthread_create(&data->tid[0], NULL, &routine, &data->philos[0]))
		return (error(TH_ERR, data));
	pthread_mutex_unlock(&data->lock);
	while (check_death(data) != 1)
		ft_usleep(50);
	pthread_join(data->tid[0], NULL);
	ft_exit(data);
	return (0);
}
