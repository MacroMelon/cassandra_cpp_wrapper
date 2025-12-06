# A (mostly) memory safe wrapper for the Datastax Cassandra C/C++ driver

![Transware](https://pride-badges.pony.workers.dev/static/v1?label=Transware&stripeWidth=8&stripeColors=5BCEFA,F5A9B8,FFFFFF,F5A9B8,5BCEFA)
![Sponsored by the Gay Agenda](https://pride-badges.pony.workers.dev/static/v1?label=Sponsored+by+the+Gay+Agenda&labelColor=%23555&stripeWidth=8&stripeColors=E40303%2CFF8C00%2CFFED00%2C008026%2C24408E%2C732982)


A C++ wrapper for the 
[Datastax Cassandra C/C++ driver](https://github.com/apache/cassandra-cpp-driver/tree/master)
meant to actually use proper C++ memory safe techniques.

It uses some heinous form of RAII that I came up with sleep deprived and high
on jaffacakes.

### I implore you, PLEASE do not use this in production environments!

Its meant to provide a simillar programming interface to the mysql xdevapi.
Simillar is doing some heavy lifting here as it currently supports veeeery
limited functionality :(