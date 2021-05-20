from plotly.offline import download_plotlyjs, init_notebook_mode, plot, iplot
from plotly.graph_objs import Scatter, Layout, Figure


def get_data_from_file(file_name):
    file_data = []
    try:
        file = open(file_name, "r+")
        for line in file:
            file_data.append(float(line))
        file.close()
        return file_data
    except IOError:
        print("Could not open "+file_name)
        return False


def main():
    data_x_interpolation = get_data_from_file("x_spline.txt")
    data_y_interpolation = get_data_from_file("y_spline.txt")
    
    data_x = get_data_from_file("x.txt")
    data_y = get_data_from_file("y.txt")
    
    data_x_nodes = get_data_from_file("x_nodes.txt")
    data_y_nodes = get_data_from_file("y_nodes.txt")
    
    if not data_x_interpolation or not data_y_interpolation  or not data_y:
        return
    
    x_axis = data_x_interpolation

    trace0 = Scatter(
        x=data_x_interpolation,
        y=data_y_interpolation,
        mode='lines',
        name='F(x)',
        line = dict(color = ('rgb(255, 0, 0)'), width=2)
    )
    
    trace1 = Scatter(
        x=data_x,
        y=data_y,
        mode='lines',
        name='f(x)',
        line = dict(color = ('rgb(50, 100, 255)'), width=2)
    )
    
    trace2 = Scatter(
        x=data_x_nodes,
        y=data_y_nodes,
        mode='markers',
        name='Nodes',
        marker = dict(color = ('rgb(255, 0, 0)'), size=8)
    )

    layout = Layout(
        yaxis=dict(
            title='wysokość [m]',
            
        ),
        yaxis2=dict(
            title='',
            range=[-150, 300],
            side='right',
            overlaying='y',
            zeroline=False,
        ),
        xaxis=dict(
            type='linear',
            title='dystans [m]',
        )
    )
   
    plot(Figure(data=[trace1, trace0, trace2], layout=layout))


if __name__ == "__main__":
    main()
