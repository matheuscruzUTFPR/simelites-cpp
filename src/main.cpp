#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <string>

// Erro do Boost

#include <boost/system/error_code.hpp>

// String do Boost

// #include <boost/algorithm/string.hpp>

// Mensagem processos
#include <boost/mpi.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>

// // Serializacao

// #include <boost/serialization/string.hpp>

// // Conexoes

// #include <boost/asio/connect.hpp>
// #include <boost/asio/ip/tcp.hpp>
// #include <boost/asio/ip/udp.hpp>
// #include <boost/asio/use_future.hpp>
// #include <boost/asio/awaitable.hpp>
// #include <boost/asio/detached.hpp>
// #include <boost/asio/co_spawn.hpp>
// #include <boost/asio/io_context.hpp>
// #include <boost/asio/read_until.hpp>
// #include <boost/asio/redirect_error.hpp>
// #include <boost/asio/signal_set.hpp>
// #include <boost/asio/steady_timer.hpp>
// #include <boost/asio/use_awaitable.hpp>
// #include <boost/asio/write.hpp>

// Log

#define BOOST_LOG_DYN_LINK 1 // antes do log

#include <boost/log/trivial.hpp>

// GIS e geometria

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

// // threads de evento

// #include <boost/fiber/mutex.hpp>
// #include <boost/fiber/operations.hpp>

// // co-rotinas, quase threads, são cooperativas, sem acesso núcleo na mudanca
// #include <boost/coroutine2/all.hpp>

// PostgreSQL

#include "../../dbinfo.inc"
#include <libpq-fe.h>


using namespace std;
namespace mpi = boost::mpi; // from <boost/mpi.hpp>
namespace mt = mpi::threading;

// namespace asio = boost::asio; // from <boost/asio.hpp>
// using boost::asio::ip::udp;

// namespace ip = boost::asio::ip; // from <boost/asio/ip/tcp.hpp>

namespace geom = boost::geometry;         // from <boost/geometry.hpp>
namespace geomi = boost::geometry::index; // from <boost/geometry.hpp>

void print(const boost::system::error_code & /*e*/)
{
    std::cout << "Hello, world!" << std::endl;
}

int main(int argc, char *argv[])
{
    boost::mpi::environment env(mt::funneled);
    if (env.thread_level() < mt::funneled)
    {
        env.abort(-1);
    }
    mpi::communicator world;
    string node_name(env.processor_name());
    //unsigned int rank(world.rank()), cpu_num(world.size());
    cout << "Testanto MPI: \n";
    unsigned rank = world.rank();
    if (rank == 0)
        cout << "Master - ";
    else
        cout << "Slave - ";
    cout << "Host: " << node_name << " rank: (" << rank + 1 << "/" << world.size() << ")\n";
    if (world.rank() == 0)
    {
        mpi::request reqs[2];
    }
    else
    {
        mpi::request reqs[2];        
    }

    std::srand(time(0) + world.rank());
    int my_number = std::rand();
    if (world.rank() == 0)
    {
        std::vector<int> all_numbers;
        gather(world, my_number, all_numbers, 0);
        for (int proc = 0; proc < world.size(); ++proc)
            std::cout << "Process #" << proc << " thought of "
                      << all_numbers[proc] << std::endl;
    }
    else
    {
        gather(world, my_number, 0);
    }
    if (world.rank() == 0)
    {
        cout << "Testanto Logs no Master: \n";
        BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
        BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
        BOOST_LOG_TRIVIAL(info) << "An informational severity message";
        BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
        BOOST_LOG_TRIVIAL(error) << "An error severity message";
        BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
    }
    if (world.rank() == 0)
    {
        cout << "Testanto GIS no Master: \n";

        geom::model::d2::point_xy<int> p1(1, 1), p2(2, 2);
        cout << "Distance p1-p2 is: " << geom::distance(p1, p2) << std::endl;

        cout << "Testando Conexão Postgresql: \n";

        const char *conninfo = DB_CONNECTION;
        PGconn *conn = PQconnectdb(conninfo);
        PGresult *res;

        /* Check to see that the backend connection was successfully made */
        if (PQstatus(conn) != CONNECTION_OK)
        {
            fprintf(stderr, "%s[%d]: Connection to database failed: %s\n",
                    __FILE__, __LINE__, PQerrorMessage(conn));
            PQfinish(conn);
            return 1;
        }
        else
        {
            cout << "Connection to database succeed.\n";
        }

        cout << "Testando Conexão Postgresql do Amazon: \n";

        if (PQstatus(conn) == CONNECTION_OK)
        {
            res = PQexec(conn,
                         "SELECT ogc_fid, bairro, ST_AsText(wkb_geometry) FROM ocupacao_irregular LIMIT 5000");

            int rows = PQntuples(res);

            typedef geom::model::d2::point_xy<double> point_type;
            std::ofstream svg("ocupacao_irregular.svg");
            boost::geometry::svg_mapper<point_type> mapper(svg, 500, 500);

            geom::model::polygon<point_type> poligonos[5000];

            cout << "Id: " << PQgetvalue(res, 1, 0) << " Bairro: " << PQgetvalue(res, 1, 1) << " Geometria: " << PQgetvalue(res, 1, 2) << endl;
            cout << "Id: " << PQgetvalue(res, 2, 0) << " Bairro: " << PQgetvalue(res, 2, 1) << " Geometria: " << PQgetvalue(res, 2, 2) << endl;

            for (int i = 0; i < rows; i++)
            {

                //cout << "Id: " << PQgetvalue(res, i, 0) << " Bairro: " << PQgetvalue(res, i, 1) << " Geometria: " << PQgetvalue(res, i, 2) << endl;
                //geoms[i] = PQgetvalue(res, i, 20);

                //cout << PQgetvalue(res, i, 20);
                //string teste = PQgetvalue(res, i, 2);
                //cout << teste;
                //geom::read_wkt(teste, b);
                //mapper.add(b);

                //geom::read_wkt(PQgetvalue(res, i, 20),b);
                string poligono;
                poligono = PQgetvalue(res, i, 2);
                geom::read_wkt(poligono, poligonos[i]);
                mapper.add(poligonos[i]);
            }
            cout << "Testando SVG: \n";
            cout << "Criado ocupacao_irregular.svg! \n";

            for (int i = 0; i < 5000; i++)
                mapper.map(poligonos[i], "fill-opacity:0.1;fill:rgb(51,51,153);stroke:rgb(153,204,0);stroke-width:0.1");

            PQclear(res);
        }
        PQfinish(conn);
    }

    cout << "Testando servidor assincrono: \n";

    return 0;
}