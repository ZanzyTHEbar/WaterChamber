import React from "react";
import * as BsIcons from "react-icons/bs";
import * as FaIcons from "react-icons/fa";
//import * as AiIcons from 'react-icons/ai';
//import * as IoIcons from 'react-icons/io';
//https://react-icons.github.io/react-icons/

export const SidebarData = [
    {
        title: "IP Address",
        icon: <FaIcons.FaServer />,
        cName: "nav-text",
        id: "ip",
        tooltip: "IP Address of the server",
    },
    {
        title: "Endpoint",
        icon: <FaIcons.FaLink />,
        cName: "nav-text",
        id: "endpoint",
        tooltip: "Endpoint of the server",
    },
    {
        title: "Title",
        icon: <FaIcons.FaPencilAlt />,
        cName: "nav-text",
        id: "title",
        tooltip: "Title of the graph",
    },
    {
        title: "Y Axis Title",
        icon: <BsIcons.BsGraphDown />,
        cName: "nav-text",
        id: "y_axis_title",
        tooltip: "Y Axis Title",
    },
    {
        title: "Line Color",
        icon: <FaIcons.FaEyeDropper />,
        cName: "nav-text",
        id: "line_color",
        tooltip: "Graph Line Color",
    },
    {
        title: "Graph ID",
        icon: <FaIcons.FaHashtag />,
        cName: "nav-text",
        id: "graph_number",
        tooltip: "Unique Graph Identifier",
    },
];
