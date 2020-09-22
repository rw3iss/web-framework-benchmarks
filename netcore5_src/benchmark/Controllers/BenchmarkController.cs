using System;
using System.Collections.Generic;
using System.Linq;
using System.Data;
using System.Data.Common;
using System.Threading.Tasks;
using System.Threading.Channels;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using MySqlConnector;

namespace benchmark.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class BenchmarkController : ControllerBase
    {
        // The Web API will only accept tokens 1) for users, and 2) having the "access_as_user" scope for this API
        //static readonly string[] scopeRequiredByApi = new string[] { "access_as_user" };

        internal AppDb Db { get; set; }

        public BenchmarkController(AppDb db)
        {
            Db = db;
        }

        [HttpGet("json")]
        public User JsonTest()
        {
            var user = new User();
            user.Id = 1;
            user.Username = "username";
            user.Email = "email";
            return user;
        }

        [HttpGet]
        public async Task<IActionResult> QueryTest()
        {
            await Db.Connection.OpenAsync();
            var cmd = Db.Connection.CreateCommand();

            // Simulate parameterized query
            cmd.CommandText = @"SELECT `Id`, `Username`, `Email` FROM `users` WHERE `Id` = @id";
            cmd.Parameters.Add(new MySqlParameter
            {
                ParameterName = "@id",
                DbType = DbType.Int32,
                Value = 1,
            });

            User user = null;
            var reader = await cmd.ExecuteReaderAsync();

            if (reader.Read())
            {
                user  = new User()
                {
                    Id = reader.GetInt32(0),
                    Username = reader.GetString(1),
                    Email = reader.GetString(2),
                };

                //user = new User((int)reader["Id"], reader["Username"].ToString(), , reader["Email"].ToString());
            }

            if (user is null)
                return new NotFoundResult();

            return new OkObjectResult(user);
        }
        
        [HttpPost]
        public async Task<IActionResult> WriteTest()
        {
            await Db.Connection.OpenAsync();
            var cmd = Db.Connection.CreateCommand();

            cmd.CommandText = @"INSERT INTO `Users` (`Username`, `Email`) VALUES ('username', 'email@email.com');";
            await cmd.ExecuteNonQueryAsync();

            var Id = (int) cmd.LastInsertedId;

            return new OkObjectResult(Id);
        }
    }
}
