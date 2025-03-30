#include "../../lib/philo.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	messages(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp(DIED, str) == 0 && check_death(philo->data) == 0)
	{
		printf("%lu %d %s\n", time, philo->id, str);
		change_death(philo->data);
	}
	if (!check_death(philo->data))
		printf("%lu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	take_forks(t_philo *philo)
{
	int	nb_phil;

	nb_phil = philo->data->philo_num;
	if (nb_phil == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		messages(TAKE_FORKS, philo);
		ft_usleep(philo->data->death_time);
	}
	else if (philo->id == nb_phil)
	{
		pthread_mutex_lock(philo->r_fork);
		messages(TAKE_FORKS, philo);
		pthread_mutex_lock(philo->l_fork);
		messages(TAKE_FORKS, philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		messages(TAKE_FORKS, philo);
		pthread_mutex_lock(philo->r_fork);
		messages(TAKE_FORKS, philo);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->data->philo_num != 1)
		pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	messages(SLEEPING, philo);
	ft_usleep(philo->data->sleep_time);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_time;
	messages(EATING, philo);
	philo->eat_cont++;
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
