// dotnet minimal API Program.cs
var builder = WebApplication.CreateBuilder(args);

// Opt in cors
builder.Services.AddCors();

var app = builder.Build();

if (app.Environment.IsDevelopment())
{
    app.UseDeveloperExceptionPage();
}

app.MapGet("/", () => "Hello World!");

app.MapGet("/sample/student", () => {
    return Results.Ok(new {
        age = 20,
        name = "jason",
    });
});

// This endpoint return the student after 10 seconds and keep the HTTP connection open
app.MapGet("/sample/studentlong", async () => {
    await Task.Delay(10000);

    return Results.Ok(new {
        age = 20,
        name = "jason",
    });
});

// Set CORS headers or with [EnableCors] attribute
// dotnet set cors headers
app.UseCors(builder => builder
    .AllowAnyOrigin()
    .AllowAnyMethod()
    .AllowAnyHeader()
);


app.Run();
