/* eslint-disable jsx-a11y/anchor-is-valid */
//import { useState } from "react";
import { SidebarData } from "@components/SettingsPageData";
import Tooltip from "@components/Tooltip";

//! TODO: Add a function to onClick button that saves the settings to a json file

//! TODO: Add setting to choose the number of charts to display

export default function Settings() {
    return (
        <div className="overflow-y-auto py-4 px-3 bg-gray-50 rounded dark:bg-gray-300 z-40">
            <div className="flex items-center justify-center">
                <header
                    style={{
                        color: "#059e8a",
                    }}
                    className="text-2xl font-bold"
                >
                    Settings
                </header>
            </div>
            <div>
                <ul className="flow-root space-y-2 items-center content-center justify-center flex-col">
                    {SidebarData.map((item, index) => (
                        <li
                            key={index}
                            className={`${item.cName} pt-2.5 pr-2.5 rounded-xl self-center items-stretch content-center justify-center mr-32 flex-row`}
                        >
                            <Tooltip tooltip={item.tooltip}>
                                <label
                                    className="float-left space-x-2 rounded-sm whitespace-nowrap"
                                    htmlFor={item.id}
                                >
                                    <span className="text-gray-700 dark:text-gray-600">
                                        {item.icon}
                                    </span>
                                    <span className="text-sm font-medium text-gray-700 dark:text-gray-500">
                                        {item.title}
                                    </span>
                                </label>
                            </Tooltip>
                            <div className="float-right">
                                <input
                                    title=""
                                    type="text"
                                    id={item.id}
                                    className="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500"
                                    placeholder={item.title}
                                    required
                                />
                            </div>
                        </li>
                    ))}
                    <button className="ml-auto bg-blue-700 hover:bg-blue-800 focus:outline-none text-white font-medium text-sm rounded-lg py-2.5 px-5 text-rounded mr-5 shadow-md hover:shadow-xl focus:bg-blue-600 transition duration-100 ease-in focus:shadow-inner">
                        Save
                    </button>
                </ul>
            </div>
            <div
                id="dropdown-cta"
                className="p-4 mt-6 bg-blue-50 rounded-lg dark:bg-blue-900"
                role="alert"
            >
                <div className="flex items-center mb-3">
                    <span className="bg-blue-100 text-blue-800 text-sm font-semibold mr-2 px-2.5 py-0.5 rounded dark:bg-blue-200 dark:text-blue-900">
                        Info
                    </span>
                    <button
                        type="button"
                        className="ml-auto -mx-1.5 -my-1.5 bg-blue-50 text-blue-900 rounded-lg focus:ring-2 focus:ring-blue-400 p-1 hover:bg-blue-200 inline-flex h-6 w-6 dark:bg-blue-900 dark:text-blue-400 dark:hover:bg-blue-800"
                        data-collapse-toggle="dropdown-cta"
                        aria-label="Close"
                    >
                        <span className="sr-only">Close</span>
                        <svg
                            aria-hidden="true"
                            className="w-4 h-4"
                            fill="currentColor"
                            viewBox="0 0 20 20"
                            xmlns="http://www.w3.org/2000/svg"
                        >
                            <path
                                fillRule="evenodd"
                                d="M4.293 4.293a1 1 0 011.414 0L10 8.586l4.293-4.293a1 1 0 111.414 1.414L11.414 10l4.293 4.293a1 1 0 01-1.414 1.414L10 11.414l-4.293 4.293a1 1 0 01-1.414-1.414L8.586 10 4.293 5.707a1 1 0 010-1.414z"
                                clipRule="evenodd"
                            />
                        </svg>
                    </button>
                </div>
                <p className="mb-3 text-sm text-blue-900 dark:text-blue-400">
                    Your URL is{" "}
                    <u>
                        <em
                            style={{
                                color: "red",
                            }}
                        >
                            required
                        </em>
                    </u>{" "}
                    to be set in order to use the app. Please enter your URL in
                    the settings. The URL must be a valid URL for a <b>GET</b>{" "}
                    request.
                </p>
            </div>
        </div>
    );
}