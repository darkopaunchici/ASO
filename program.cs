using TodoApp;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

List<TodoItem> todos = new();
int nextId = 1;

app.MapGet("/", () => "Aplicatie TODO ASP.NET Core");

app.MapGet("/todos", () => todos);

app.MapGet("/todos/{id}", (int id) =>
{
    var todo = todos.FirstOrDefault(t => t.Id == id);

    return todo is not null
        ? Results.Ok(todo)
        : Results.NotFound("Sarcina nu a fost gasita.");
});

app.MapPost("/todos", (TodoItem item) =>
{
    item.Id = nextId++;
    todos.Add(item);

    return Results.Created($"/todos/{item.Id}", item);
});

app.MapPut("/todos/{id}", (int id, TodoItem updatedItem) =>
{
    var todo = todos.FirstOrDefault(t => t.Id == id);

    if (todo is null)
        return Results.NotFound("Sarcina nu exista.");

    todo.Title = updatedItem.Title;
    todo.IsDone = updatedItem.IsDone;

    return Results.Ok(todo);
});

app.MapDelete("/todos/{id}", (int id) =>
{
    var todo = todos.FirstOrDefault(t => t.Id == id);

    if (todo is null)
        return Results.NotFound("Sarcina nu exista.");

    todos.Remove(todo);

    return Results.Ok("Sarcina a fost stearsa.");
});

app.Run();