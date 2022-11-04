/* eslint-disable jsx-a11y/anchor-is-valid */
import React from "react";

export default function Sidebar(props) {
    return (
        <div>
            <aside className="w-64" aria-label="Sidebar">
                <div className="overflow-y-auto py-4 px-3 bg-gray-50 rounded dark:bg-gray-300 z-40">
                    <a href="#" className="flex items-center pl-2.5 mb-5">
                        <img
                            src="/images/icons/Square30x30Logo.png"
                            className="mr-3 h-6 sm:h-9"
                            alt="Logo"
                        />
                        <span className="self-center text-xl font-semibold whitespace-nowrap dark:text-white">
                            {props.name}
                        </span>
                    </a>
                    <ul className="space-y-2">
                        <header
                            style={{
                                color: "#059e8a",
                            }}
                        >
                            Settings
                        </header>
                        <li className="px-2 py-1 rounded-sm dark:hover:bg-gray-400">
                            <a
                                href="#"
                                className="flex items-center space-x-2 p-2 rounded-sm dark:hover:bg-gray-400"
                            >
                                <span className="text-gray-600 dark:text-gray-500">
                                    <svg
                                        className="w-6 h-6"
                                        fill="none"
                                        stroke="currentColor"
                                        viewBox="0 0 24 24"
                                        xmlns="http://www.w3.org/2000/svg"
                                    >
                                        <path
                                            strokeLinecap="round"
                                            strokeLinejoin="round"
                                            strokeWidth="2"
                                            d="M9 5l7 7-7 7"
                                        />
                                    </svg>
                                </span>
                            </a>
                        </li>
                    </ul>
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
                                        fill-rule="evenodd"
                                        d="M4.293 4.293a1 1 0 011.414 0L10 8.586l4.293-4.293a1 1 0 111.414 1.414L11.414 10l4.293 4.293a1 1 0 01-1.414 1.414L10 11.414l-4.293 4.293a1 1 0 01-1.414-1.414L8.586 10 4.293 5.707a1 1 0 010-1.414z"
                                        clip-rule="evenodd"
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
                            to be set in order to use the app. Please enter your
                            URL in the settings. The URL must be a valid URL for
                            a <b>GET</b> request.
                        </p>
                    </div>
                </div>
            </aside>
        </div>
    );
}
