# A (mostly) memory safe wrapper for the Datastax Cassandra C/C++ driver

![Transware](https://pride-badges.pony.workers.dev/static/v1?label=Transware&stripeWidth=8&stripeColors=5BCEFA,F5A9B8,FFFFFF,F5A9B8,5BCEFA)
![Sponsored by the Gay Agenda](https://pride-badges.pony.workers.dev/static/v1?label=Sponsored+by+the+Gay+Agenda&labelColor=%23555&stripeWidth=8&stripeColors=E40303%2CFF8C00%2CFFED00%2C008026%2C24408E%2C732982)


A C++ wrapper for the 
[Datastax Cassandra C/C++ driver](https://github.com/apache/cassandra-cpp-driver/tree/master)
meant to actually use proper C++ memory safe techniques.

It uses some heinous form of RAII that I came up with while sleep deprived and high
on jaffacakes.

### I implore you, PLEASE do not use this in production environments! (yet)

Its meant to provide a simillar programming interface to the mysql xdevapi.
Simillar is doing some heavy lifting here as it currently supports veeeery
limited functionality :(

TODO - add proper commands and examples for building and usage

## Building
1) Clone this repository
2) Recursively init submodules
3) Build like a normal cmake application in some build directory

## Usage
1) Add the include folder to your project's header paths
2) Link against:
   - build_directory/libcassandra_static.a
   - build_directory/libcassandra_cpp_wrapper.a
   - OpenSSL (OpenSSL::SSL)
   - ZLib (ZLIB::ZLIB)
   - libuv
3) Use :3

   ```c++
   casswrap::SessionSettings databaseConenctionSeetings {
    .host = "192.168.1.2",
    .port = 0,   //uhhh this doesn't do anything right now
    .user = "username",
    .password = "meow",
    .keyspace = "meow_keyspace"
   };

   //or use new and a pointer
   //should be thread safe? I think? I've used it as a singleton in an event loop thingy concurrently without issues!
   //(and the underlying CassSession* pointer is thread safe so should be fine!)
   casswrap::Session cassandraSession(databaseConenctionSeetings);

   std::string cqlStr = "INSERT INTO meow_keyspace.kitty_details (kitty_uuid, type, name, num_ears) VALUES (?, ?, ?)";
   
   cassandraSession.sql(cqlStr)
                .bindUUID(kittyUuidString)
                .bind("Meowy")
                .bind(int64_t(2))
                .executeAsync();   //yeeee non-blocking is a thing!

   //and to get stuff:
   
   std::string cqlString = "SELECT name, num_ears FROM meow_keyspace.kitty_details WHERE type = ?";
   casswrap::RowResult results cassandraSession.sql(cqlStr).bind("mainecoon").execute();
   
   //results.count() returns the number of rows in the result of the operation
   for (int rowIndex = 0; rowIndex < results.count(); rowIndex++){
   
      //everytime its called, fetchOne() will return the next consecutive row
      //each row is an "array" of values (each element is the value of the corresponding queried column)
      std::cout << "Name: " << results.fetchOne()[0].getString(); << std::endl;
   
   }
   ```
   Have a read through the .h files to see all the available functionality!
